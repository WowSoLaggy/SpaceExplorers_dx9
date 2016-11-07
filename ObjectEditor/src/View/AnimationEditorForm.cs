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
    public partial class AnimationEditorForm : Form
    {
        public AnimationEditorForm(AnimationSet pAnimationSet)
        {
            InitializeComponent();
            AnimationSet = pAnimationSet;

            bindingSource = new BindingSource();
            bindingSource.DataSource = AnimationSet.Animations;

            UpdateDataSources();
            animationsList.DataSource = null;
            animationsList.DataSource = bindingSource;
        }

        public AnimationSet AnimationSet;
        BindingSource bindingSource;


        private void btnAdd_Click(object sender, EventArgs e)
        {
            AnimationSet.Animations.Add(new Animation());
            UpdateDataSources();
        }

        private void btnDelete_Click(object sender, EventArgs e)
        {
            if (animationsList.SelectedItem == null)
                return;

            AnimationSet.Animations.Remove((Animation)animationsList.SelectedItem);
            UpdateDataSources();
        }

        private void animationsList_SelectedValueChanged(object sender, EventArgs e)
        {
            propertyGrid.SelectedObject = animationsList.SelectedItem;
        }

        private void propertyGrid_PropertyValueChanged(object s, PropertyValueChangedEventArgs e)
        {
            UpdateDataSources();
        }

        private void UpdateDataSources()
        {
            animationsList.DataSource = null;
            animationsList.DataSource = bindingSource;
        }
    }
}
