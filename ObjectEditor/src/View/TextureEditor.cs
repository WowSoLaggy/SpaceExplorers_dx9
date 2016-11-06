using ObjectEditor.src.Controller;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ObjectEditor.src.View
{
    public partial class TextureEditorForm : Form
    {
        static public TextureEditorForm GetInstance() { return m_instance; }
        static private TextureEditorForm m_instance;

        public TextureEditorForm()
        {
            InitializeComponent();
            m_instance = this;
            texturePreview.SizeMode = PictureBoxSizeMode.Zoom;
        }

        private void TextureEditor_Load(object sender, EventArgs e)
        {
            TextureController.OnTextureEditorLoaded();
        }

        private void texturesList_SelectedIndexChanged(object sender, EventArgs e)
        {
            TextureController.OnTextureSelectionChanged();
        }

        private void refreshToolStripMenuItem_Click(object sender, EventArgs e)
        {
            TextureController.Refresh();
        }

        private void propertyGrid_PropertyValueChanged(object s, PropertyValueChangedEventArgs e)
        {
            TextureController.OnTextureChanged();
        }

        private void convertToolStripMenuItem_Click(object sender, EventArgs e)
        {
            TextureController.OnConvertPress();
        }
    }
}
