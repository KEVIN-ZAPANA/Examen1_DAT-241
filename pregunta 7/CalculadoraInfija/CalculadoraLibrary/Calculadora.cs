using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CalculadoraLibrary
{
    public class Calculadora
    {
       public string Evaluar(string expresion)
        {
            try
            {
                string[] tokens = ConvertirANotacionPostfija(expresion);
                double resultado = EvaluarNotacionPostfija(tokens);
                return resultado.ToString();
            }
            catch (Exception)
            {
                return "Error";
            }
        }

        private string[] ConvertirANotacionPostfija(string expresion)
        {
            Stack<string> pila = new Stack<string>();
            List<string> resultado = new List<string>();

            string[] tokens = expresion.Trim().Split(' '); // Asegúrate de dividir por espacios

            foreach (string token in tokens)
            {
                double numero;
                if (double.TryParse(token, out numero))
                {
                    resultado.Add(token);
                }
                else if (token == "(")
                {
                    pila.Push(token);
                }
                else if (token == ")")
                {
                    while (pila.Count > 0 && pila.Peek() != "(")
                    {
                        resultado.Add(pila.Pop());
                    }
                    pila.Pop();
                }
                else
                {
                    while (pila.Count > 0 && Precedencia(token) <= Precedencia(pila.Peek()))
                    {
                        resultado.Add(pila.Pop());
                    }
                    pila.Push(token);
                }
            }

            while (pila.Count > 0)
            {
                resultado.Add(pila.Pop());
            }

            return resultado.ToArray();
        }

        private double EvaluarNotacionPostfija(string[] tokens)
        {
            Stack<double> pila = new Stack<double>();

            foreach (string token in tokens)
            {
                double numero;
                if (double.TryParse(token, out numero))
                {
                    pila.Push(numero);
                }
                else
                {
                    double b = pila.Pop();
                    double a = pila.Pop();
                    pila.Push(Calcular(a, b, token));
                }
            }

            return pila.Pop();
        }

        private double Calcular(double a, double b, string operador)
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
                    return a / b;
                default:
                    throw new ArgumentException("Operador no válido");
            }
        }

        private int Precedencia(string operador)
        {
            if (operador == "+" || operador == "-")
                return 1;
            if (operador == "*" || operador == "/")
                return 2;
            return 0;
        }
    
    }
}
