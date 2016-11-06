using ObjectEditor.src.Model;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ObjectEditor.src.Controller
{
    static class TextureLoader
    {
        static public List<TextureContainer> LoadTextures(string pTexturesDir)
        {
            List<TextureContainer> textures = new List<TextureContainer>();

            List<string> textureNames = new List<string>(Directory.GetFiles(pTexturesDir, "*.*", SearchOption.AllDirectories));
            foreach (var textureName in textureNames)
            {
                TextureContainer textureContainer = new TextureContainer();

                string fileName = Path.GetFileNameWithoutExtension(textureName);
                List<string> tokens = new List<string>(fileName.Split('_'));
                if (tokens.Count == 5)
                {
                    textureContainer.Name = tokens[0];
                    textureContainer.Width = int.Parse(tokens[1]);
                    textureContainer.Height = int.Parse(tokens[2]);
                    textureContainer.NumberOfFrames = int.Parse(tokens[3]);
                    textureContainer.CheckAlpha = (tokens[4] == "a");
                    textureContainer.Extension = Path.GetExtension(textureName);
                    textureContainer.RealFileName = Path.GetFileName(textureName);
                }
                else
                    textureContainer.Name = Path.GetFileName(textureName);

                textures.Add(textureContainer);
            }

            return textures;
        }

        static public void ConvertTextureFromName(TextureContainer textureContainer)
        {
            string fileName = Path.GetFileNameWithoutExtension(textureContainer.Name);
            string extension = Path.GetExtension(textureContainer.Name);
            List <string> tokens = new List<string>(fileName.Split('_'));

            textureContainer.Name = tokens.Count >= 1 ? tokens[0] : textureContainer.Name;
            textureContainer.Width = tokens.Count >= 2 ? int.Parse(tokens[1]) : 64;
            textureContainer.Height = tokens.Count >= 3 ? int.Parse(tokens[2]) : 64;
            textureContainer.NumberOfFrames = tokens.Count >= 4 ? int.Parse(tokens[3]) : 1;
            textureContainer.CheckAlpha = tokens.Count >= 5 ? (tokens[4] == "a") : false;

            textureContainer.Extension = extension;
        }
    }
}
