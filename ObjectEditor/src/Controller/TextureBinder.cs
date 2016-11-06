using ObjectEditor.src.Model;
using ObjectEditor.src.View;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ObjectEditor.src.Controller
{
    static class TextureBinder
    {
        static public void UpdateAll(List<TextureContainer> pTextures, TextureEditorForm pTextureEditor)
        {
            UpdateTexturesList(pTextures, pTextureEditor);
            UpdateTexturePreview(pTextures, pTextureEditor);
        }

        static public void UpdateTexturesList(List<TextureContainer> pTextures, TextureEditorForm pTextureEditor)
        {
            pTextureEditor.texturesList.DataSource = null;
            pTextureEditor.texturesList.DataSource = pTextures;
        }

        static public void RemoveTexturePreview(TextureEditorForm pTextureEditor)
        {
            if (pTextureEditor.texturePreview.Image != null)
            {
                pTextureEditor.texturePreview.Image.Dispose();
                pTextureEditor.texturePreview.Image = null;
            }
        }

        static public void UpdateTexturePreview(List<TextureContainer> pTextures, TextureEditorForm pTextureEditor)
        {
            RemoveTexturePreview(pTextureEditor);

            int index = pTextureEditor.texturesList.SelectedIndex;
            if (index < 0 || index >= pTextures.Count)
                return;

            var texture = pTextures[index];
            string fileName = "Textures\\" + texture.ToString();
            if (!File.Exists(fileName))
                return;

            try
            {
                pTextureEditor.texturePreview.Image = Bitmap.FromFile(fileName);
            }
            catch (Exception)
            {
            }
        }

        static public void UpdatePropertyWindow(List<TextureContainer> pTextures, TextureEditorForm pTextureEditor)
        {
            int index = pTextureEditor.texturesList.SelectedIndex;
            if (index < 0 || index >= pTextures.Count)
            {
                pTextureEditor.propertyGrid.SelectedObject = null;
                return;
            }

            var texture = pTextures[index];
            pTextureEditor.propertyGrid.SelectedObject = texture;
        }

        static public void OnTextureChanged(List<TextureContainer> pTextures, TextureEditorForm pTextureEditor)
        {
            int prevIndex = pTextureEditor.texturesList.SelectedIndex;
            pTextureEditor.texturesList.DataSource = null;
            pTextureEditor.texturesList.DataSource = pTextures;
            pTextureEditor.texturesList.SelectedIndex = prevIndex;
        }
    }
}
