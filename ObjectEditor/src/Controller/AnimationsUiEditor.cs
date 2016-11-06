using ObjectEditor.src.Model;
using ObjectEditor.src.View;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing.Design;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ObjectEditor.src.Controller
{
    class AnimationsUiEditor : UITypeEditor
    {
        public override UITypeEditorEditStyle GetEditStyle(ITypeDescriptorContext context)
        {
            return UITypeEditorEditStyle.Modal;
        }

        public override object EditValue(ITypeDescriptorContext context, IServiceProvider provider, object value)
        {
            AnimationEditorForm animationEditor = new AnimationEditorForm((AnimationSet)value);
            var res = animationEditor.ShowDialog(MainForm.GetInstance());
            if (res == DialogResult.OK)
                value = animationEditor.AnimationSet;

            return value;
        }
    }
}
