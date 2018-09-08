using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Sudokise3
{
    public partial class Sudokise3Form : Form
    {
        public Sudokise3Form()
        {
            InitializeComponent();

        }
        private void Sudokise3Form_KeyDown(object sender, KeyEventArgs e)
        {
            switch(e.KeyCode)
            {
                case Keys.F1:

                    break;
            }
        }

    }
}