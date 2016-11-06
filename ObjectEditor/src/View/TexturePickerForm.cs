using ObjectEditor.src.Model;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ObjectEditor.src.View
{
    public partial class TexturePickerForm : Form
    {
        public TexturePickerForm(List<TextureContainer> pTextures)
        {
            InitializeComponent();
            texturesList.DataSource = pTextures;

            DialogResult = DialogResult.Cancel;
        }

        private void texturesList_DoubleClick(object sender, EventArgs e)
        {
            if (texturesList.SelectedItem != null)
            {
                DialogResult = DialogResult.OK;
                Close();
            }
        }
    }
}
