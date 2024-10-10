using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using CalculadoraLibrary;

namespace CalculadoraInfija
{
    public partial class Form1 : Form
    {
        private Calculadora calculadora = new Calculadora();
        private string expresion = "";
        public Form1()
        {
            InitializeComponent();
        }

        private void ButtonNumber_Click(object sender, EventArgs e)
        {
            Button boton = (Button)sender;
            expresion += boton.Text + " ";
            displayLabel.Text = expresion;
        }

        private void ButtonOperator_Click(object sender, EventArgs e)
        {
            Button boton = (Button)sender;
            expresion += boton.Text + " ";
            displayLabel.Text = expresion;
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
        //clear
        private void button11_Click(object sender, EventArgs e)
        {
            expresion = "";
            displayLabel.Text = "0";
        }

        private void ButtonEqual_Click(object sender, EventArgs e)
        {
            displayLabel.Text = calculadora.Evaluar(expresion);
            expresion = displayLabel.Text; // Para continuar con el resultado
        }

    }
}
