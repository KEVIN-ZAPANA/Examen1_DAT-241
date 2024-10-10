using System;
using System.Collections.Generic;
using System.Web.Services;

[WebService(Namespace = "http://tempuri.org/")]
[WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
public class WebService : System.Web.Services.WebService
{
    public WebService() { }

    [WebMethod]
    public double EvaluarExpresionPrefija(string expresion)
    {
        var elementos = DividirElementos(expresion);
        elementos.Reverse();
        return EvaluarPrefija(elementos);
    }

    private List<string> DividirElementos(string expresion)
    {
        // División de la expresion
        var elementos = new List<string>();
        string numero = "";
        foreach (char c in expresion)
        {
            if (char.IsDigit(c) || c == '.')
                numero += c;
            else
            {
                if (numero != "") elementos.Add(numero);
                if (!char.IsWhiteSpace(c)) elementos.Add(c.ToString());
                numero = "";
            }
        }
        if (numero != "") elementos.Add(numero);
        return elementos;
    }

    private double EvaluarPrefija(List<string> elementos)
    {
        Stack<double> valores = new Stack<double>();

        double numero;
        foreach (string elemento in elementos)
        {
            if (double.TryParse(elemento, out numero))
            {
                valores.Push(numero); //pilas cada expresion en un lugar
            }
            else
            {
                // saco a los que se aplicara el operador
                double valorIzquierdo = valores.Pop();
                double valorDerecho = valores.Pop();
                //aqui hago mi operacion
                double resultado = EjecutarOperacion(valorIzquierdo, valorDerecho, elemento);
                valores.Push(resultado);
            }
        }

        return valores.Pop();
    }

    private double EjecutarOperacion(double a, double b, string operador)
    {
        switch (operador)
        {
            case "+":
                return a + b;
            case "-":
                return a - b;
            case "*":
                return a * b;
            case "/":
                if (b == 0)
                    throw new DivideByZeroException("No se puede dividir por cero");
                return a / b;
            default:
                throw new InvalidOperationException("Operador desconocido");
        }
    }
}


