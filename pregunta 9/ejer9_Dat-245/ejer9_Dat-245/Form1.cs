using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ejer9_Dat_245
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }
        //bot para cargar la imagen
        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog dialogoAbrir = new OpenFileDialog();
            dialogoAbrir.Filter = "Archivos de imagen|*.jpg;*.jpeg;*.png;*.bmp";

            if (dialogoAbrir.ShowDialog() == DialogResult.OK)
            {
                pictureBox1.Image = new Bitmap(dialogoAbrir.FileName);
            }
        }
        //bot para detectar bordes
        private void button2_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                // Convertir la imagen del PictureBox a Bitmap
                Bitmap imagenEntrada = new Bitmap(pictureBox1.Image);
                Bitmap imagenBordes = detecBorde(imagenEntrada);
                pictureBox1.Image = imagenBordes;
            }
            else
            {
                MessageBox.Show("Por favor, carga una imagen primero.");
            }
        }

        private Bitmap detecBorde(Bitmap imagenEntrada)
        {
            Bitmap imagenGris = new Bitmap(imagenEntrada.Width, imagenEntrada.Height);

            for (int fila = 0; fila < imagenEntrada.Height; fila++)
            {
                for (int columna = 0; columna < imagenEntrada.Width; columna++)
                {
                    Color pixel = imagenEntrada.GetPixel(columna, fila);
                    int escalaGris = (int)((pixel.R * 0.3) + (pixel.G * 0.59) + (pixel.B * 0.11));
                    imagenGris.SetPixel(columna, fila, Color.FromArgb(escalaGris, escalaGris, escalaGris));
                }
            }

            int[,] filtroGx = new int[,]
            {
                { -1, 0, 1 },
                { -2, 0, 2 },
                { -1, 0, 1 }
            };

            int[,] filtroGy = new int[,]
            {
                { -1, -2, -1 },
                { 0, 0, 0 },
                { 1, 2, 1 }
            };

            Bitmap imagenBordes = new Bitmap(imagenEntrada.Width, imagenEntrada.Height);

            for (int fila = 1; fila < imagenEntrada.Height - 1; fila++)
            {
                for (int columna = 1; columna < imagenEntrada.Width - 1; columna++)
                {
                    int gradienteX = 0;
                    int gradienteY = 0;

                    for (int i = -1; i <= 1; i++)
                    {
                        for (int j = -1; j <= 1; j++)
                        {
                            Color pixel = imagenGris.GetPixel(columna + j, fila + i);
                            gradienteX += filtroGx[i + 1, j + 1] * pixel.R;
                            gradienteY += filtroGy[i + 1, j + 1] * pixel.R;
                        }
                    }

                    int gradiente = (int)Math.Sqrt((gradienteX * gradienteX) + (gradienteY * gradienteY));
                    gradiente = Math.Min(255, Math.Max(0, gradiente));
                    imagenBordes.SetPixel(columna, fila, Color.FromArgb(gradiente, gradiente, gradiente));
                }
            }

            return imagenBordes;
        }
    }
}
