using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Demo
{
    public partial class Form2 : Form
    {
        public Form2() => InitializeComponent();
        private void button1_Click(object sender, EventArgs e)
        {
            MSGFormat("Textboxes : {0}", richTextBox1.Text == richTextBox2.Text ? "Match" : "Not match");
        }
        public void MSGFormat(string format, params object[] args)
        {
            MessageBox.Show(String.Format(format, args));
        }
    }
}