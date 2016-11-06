using ObjectEditor.src.Model;
using ObjectEditor.src.View;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ObjectEditor.src.Controller
{
    static class TextureController
    {
        static private List<TextureContainer> m_textures = new List<TextureContainer>();
        static public List<TextureContainer> GetTextures() { return m_textures; }


        static public void OnTextureEditorLoaded()
        {
            Refresh();
        }

        static public void Refresh()
        {
            UpdateTextures();
            TextureBinder.UpdateAll(m_textures, TextureEditorForm.GetInstance());
        }

        static public void UpdateTextures()
        {
            m_textures = TextureLoader.LoadTextures(Directory.GetCurrentDirectory() + "\\Textures\\");
        }

        static public void OnTextureSelectionChanged()
        {
            TextureBinder.UpdateTexturePreview(m_textures, TextureEditorForm.GetInstance());
            TextureBinder.UpdatePropertyWindow(m_textures, TextureEditorForm.GetInstance());

            var item = TextureEditorForm.GetInstance().texturesList.SelectedItem;
            if (item != null && !(item as TextureContainer).IsCorrectFormat())
                TextureEditorForm.GetInstance().convertToolStripMenuItem.Enabled = true;
            else
                TextureEditorForm.GetInstance().convertToolStripMenuItem.Enabled = false;
        }

        static public void OnTextureChanged()
        {
            var item = TextureEditorForm.GetInstance().texturesList.SelectedItem;
            if (item == null)
                return;

            TextureBinder.RemoveTexturePreview(TextureEditorForm.GetInstance());

            string oldFileName = (item as TextureContainer).RealFileName;
            File.Move("Textures\\" + oldFileName, "Textures\\" + item.ToString());

            (item as TextureContainer).RealFileName = item.ToString();

            TextureBinder.OnTextureChanged(m_textures, TextureEditorForm.GetInstance());
        }

        static public void OnConvertPress()
        {
            var item = TextureEditorForm.GetInstance().texturesList.SelectedItem;
            if (item == null)
                return;

            string prevFileName = item.ToString();

            TextureLoader.ConvertTextureFromName((TextureContainer)item);
            TextureBinder.OnTextureChanged(m_textures, TextureEditorForm.GetInstance());

            File.Move("Textures\\" + prevFileName, "Textures\\" + item.ToString());

            TextureBinder.UpdateTexturePreview(m_textures, TextureEditorForm.GetInstance());
        }
    }
}
