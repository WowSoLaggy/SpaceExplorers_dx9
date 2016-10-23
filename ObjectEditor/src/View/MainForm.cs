using ObjectEditor.src.Controller;
using System;
using System.IO;
using System.Windows.Forms;

namespace ObjectEditor
{
    public partial class MainForm : Form
    {
        static public MainForm GetInstance() { return m_instance; }
        static private MainForm m_instance;

        public MainForm()
        {
            InitializeComponent();
            m_instance = this;
            saveFileDialog.InitialDirectory = Directory.GetCurrentDirectory();
            texturePreview.SizeMode = PictureBoxSizeMode.Zoom;
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            Controller.OnViewLoaded();
        }

        public void SetText(string pText = "")
        {
            Text = "SpaceExplorers Object Editor" + pText;
        }

        private void newobjsFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Controller.NewDocument();
        }

        private void closeobjsFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Controller.CloseDocument();
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (Controller.TryExit())
                Close();
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Controller.SaveDocument();
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var res = saveFileDialog.ShowDialog(this);
            if (res == DialogResult.OK && !string.IsNullOrEmpty(saveFileDialog.FileName))
                Controller.SaveAsDocument(saveFileDialog.FileName);
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var res = openFileDialog.ShowDialog(this);
            if (res == DialogResult.OK && !string.IsNullOrEmpty(openFileDialog.FileName))
                Controller.OpenDocument(openFileDialog.FileName);
        }

        private void addNewObjectToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Controller.CreateNewThing();
        }

        private void deleteObjectToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Controller.DeleteThing();
        }

        private void treeThings_AfterSelect(object sender, TreeViewEventArgs e)
        {
            Controller.ThingSelectionChanged();
        }

        private void treeThings_AfterLabelEdit(object sender, NodeLabelEditEventArgs e)
        {
            Controller.TryRenameThing(ref e);
        }

        private void propertyGrid_PropertyValueChanged(object s, PropertyValueChangedEventArgs e)
        {
            Controller.OnThingChanged();
        }
    }
}
