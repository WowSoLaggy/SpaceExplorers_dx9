using System;
using ObjectEditor.src.Model;
using System.Collections.Generic;
using System.Windows.Forms;
using System.IO;

namespace ObjectEditor.src.Controller
{
    static class Controller
    {
        static Controller()
        {
        }


        static private Document m_curDocument;


        static public void OnViewLoaded()
        {
            // Try to load the default .objs file
            var res = OpenDocument(Directory.GetCurrentDirectory() + "\\main.objs", true);

            UpdateMainCaption();
            UpdateButtonsVisibility();

            if (!res)
                SetStatus("Ready: Editor started");
        }


        static public void NewDocument()
        {
            Document document = new Document(GetNewDocumentName());
            SetCurDocument(document);

            SetStatus("Ready: New document \"" + document.FileName + "\" created.");
        }


        static public bool CloseDocument()
        {
            var res = SetCurDocument(null);
            SetStatus("Ready: Document closed.");
            return res;
        }


        static public bool TryExit()
        {
            return CloseDocument();
        }


        static public bool OpenDocument(string pFilePath, bool pSilentMode = false)
        {
            var document = DocumentSaverLoader.Load(pFilePath);
            if (document == null)
            {
                if (!pSilentMode)
                    MessageBox.Show("Error while loading things.");
                return false;
            }

            SetCurDocument(document);
            SetStatus("Ready: Document \"" + document.FileName + "\" loaded.");

            return true;
        }


        static public void SaveDocument()
        {
            if (m_curDocument == null)
                return;

            DocumentSaverLoader.Save(m_curDocument);
            UpdateMainCaption();

            SetStatus("Ready: Document \"" + m_curDocument.FileName + "\" saved.");
        }


        static public void SaveAsDocument(string pFileName)
        {
            if (m_curDocument == null)
                return;

            m_curDocument.FileName = pFileName;
            SaveDocument();
        }


        static private bool SetCurDocument(Document pDocument)
        {
            if (m_curDocument != null && m_curDocument.Changed)
            {
                var dialogRes = MessageBox.Show(MainForm.GetInstance(), "All unsaved changes will be lost. Save current document?", "Not saved changes",
                    MessageBoxButtons.YesNoCancel, MessageBoxIcon.Warning);

                if (dialogRes == DialogResult.Cancel)
                    return false;
                else if (dialogRes == DialogResult.Yes)
                    SaveDocument();
            }

            m_curDocument = pDocument;
            UpdateMainCaption();
            UpdateButtonsVisibility();

            DocumentBinder.UpdateAll(m_curDocument, MainForm.GetInstance());

            return true;
        }

        static private void UpdateMainCaption()
        {
            if (m_curDocument == null)
            {
                MainForm.GetInstance().SetText();
                return;
            }

            if (m_curDocument.Changed)
                MainForm.GetInstance().SetText(" - " + m_curDocument.FileName + " *");
            else
                MainForm.GetInstance().SetText(" - " + m_curDocument.FileName);
        }


        static private void UpdateButtonsVisibility()
        {
            bool docExists = (m_curDocument != null);

            var mainForm = MainForm.GetInstance();

            mainForm.saveToolStripMenuItem.Enabled = docExists;
            mainForm.saveAsToolStripMenuItem.Enabled = docExists;
            mainForm.closeobjsFileToolStripMenuItem.Enabled = docExists;
            mainForm.objectsToolStripMenuItem.Enabled = docExists;
        }


        static private string GetNewDocumentName()
        {
            string fileNameBase = Directory.GetCurrentDirectory() + "\\NewThings";
            string fileNamePostfix = ".objs";

            string fileName = fileNameBase + fileNamePostfix;
            int fileNumber = 0;
            while (File.Exists(fileName))
            {
                ++fileNumber;
                fileName = fileNameBase + fileNumber + fileNamePostfix;
            }

            return fileName;
        }


        static private void SetStatus(string pText)
        {
            MainForm.GetInstance().toolStripStatusLabel1.Text = pText;
        }


        static public void ThingSelectionChanged()
        {
            TreeNode node = MainForm.GetInstance().treeThings.SelectedNode;
            if (node.Parent == null)
                MainForm.GetInstance().deleteObjectToolStripMenuItem.Enabled = false;
            else
                MainForm.GetInstance().deleteObjectToolStripMenuItem.Enabled = true;

            DocumentBinder.UpdateThingTextureWindow(m_curDocument, MainForm.GetInstance());
            DocumentBinder.UpdatePropertyWindow(m_curDocument, MainForm.GetInstance());
        }


        static public void CreateNewThing()
        {
            var newThing = new RealThing(GetNewThingName());
            m_curDocument.Things.Add(newThing);
            m_curDocument.Changed = true;
            UpdateMainCaption();
            DocumentBinder.UpdateAll(m_curDocument, MainForm.GetInstance());

            SetStatus("Thing \"" + newThing.TypeName + "\" created.");
        }


        static public void DeleteThing()
        {
            TreeNode node = MainForm.GetInstance().treeThings.SelectedNode;
            string nameToDelete = node.Text;
            m_curDocument.Things.RemoveAll(thing => thing.TypeName == nameToDelete);
            m_curDocument.Changed = true;
            UpdateMainCaption();
            DocumentBinder.UpdateAll(m_curDocument, MainForm.GetInstance());

            SetStatus("Thing \"" + nameToDelete + "\" deleted.");
        }


        static public string GetNewThingName()
        {
            string thingNameBase = "NewThing";
            string thingName = thingNameBase;
            int count = 0;
            while (m_curDocument.Things.Find(thing => thing.TypeName == thingName) != null)
            {
                ++count;
                thingName = thingNameBase + count;
            }
            return thingName;
        }


        static public void TryRenameThing(ref NodeLabelEditEventArgs e)
        {
            if (string.IsNullOrEmpty(e.Label))
            {
                e.CancelEdit = true;
                return;
            }

            if (string.IsNullOrWhiteSpace(e.Label))
            {
                e.CancelEdit = true;
                MessageBox.Show("Awww, common, you can't come up with a better name?", "Can't rename", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if (e.Node.Parent == null)
            {
                e.CancelEdit = true;
                MessageBox.Show("I knew you will do it");
                return;
            }

            
            string newTypeName = e.Label;
            var newThing = m_curDocument.Things.Find(thing => thing.TypeName == newTypeName);
            if (newThing != null)
            {
                e.CancelEdit = true;
                MessageBox.Show("Thing with this name already exists", "Can't rename", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            string oldTypeName = e.Node.Text;
            var oldThing = m_curDocument.Things.Find(thing => thing.TypeName == oldTypeName);
            oldThing.TypeName = newTypeName;

            MainForm.GetInstance().propertyGrid.Refresh();
        }


        static public void OnThingChanged()
        {
            m_curDocument.Changed = true;
            UpdateMainCaption();
            DocumentBinder.UpdateThingTextureWindow(m_curDocument, MainForm.GetInstance());
        }
    }
}
