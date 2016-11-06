using ObjectEditor.src.Model;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace ObjectEditor.src.Controller
{
    static class DocumentBinder
    {

        static public void UpdateAll(Document pDocument, MainForm pMainForm)
        {
            if (pMainForm == null)
                return;

            UpdateTreeThings(pDocument, pMainForm);
            UpdateThingTextureWindow(pDocument, pMainForm);
            UpdatePropertyWindow(pDocument, pMainForm);
        }


        static public void UpdateTreeThings(Document pDocument, MainForm pMainForm)
        {
            var nodes = pMainForm.treeThings.Nodes;
            nodes.Clear();

            if (pDocument == null)
                return;

            var rootNode = nodes.Add("Objects");


            foreach (var thing in pDocument.Things)
                rootNode.Nodes.Add(thing.TypeName);


            rootNode.ExpandAll();
        }


        static public void UpdateThingTextureWindow(Document pDocument, MainForm pMainForm)
        {
            RemoveTexturePreview(pMainForm);

            var node = pMainForm.treeThings.SelectedNode;
            if (node == null || node.Parent == null)
                return;


            var thing = pDocument.Things.Find(pThing => pThing.TypeName == node.Text);
            string fileName = "Textures\\" + thing.Texture.ToString();
            if (string.IsNullOrEmpty(thing.Texture.ToString()) || !File.Exists(fileName))
                return;


            try
            {
                pMainForm.texturePreview.Image = Bitmap.FromFile(fileName);
            }
            catch (Exception)
            {
            }
        }


        static public void RemoveTexturePreview(MainForm pMainForm)
        {
            if (pMainForm.texturePreview.Image != null)
            {
                pMainForm.texturePreview.Image.Dispose();
                pMainForm.texturePreview.Image = null;
            }
        }


        static public void UpdatePropertyWindow(Document pDocument, MainForm pMainForm)
        {
            var node = pMainForm.treeThings.SelectedNode;
            if (node == null || node.Parent == null)
            {
                pMainForm.propertyGrid.SelectedObject = null;
                return;
            }
            var thing = pDocument.Things.Find(pThing => pThing.TypeName == node.Text);
            pMainForm.propertyGrid.SelectedObject = thing;
        }

    }
}
