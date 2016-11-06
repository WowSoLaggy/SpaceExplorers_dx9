namespace ObjectEditor.src.View
{
    partial class TexturePickerForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.texturesList = new System.Windows.Forms.ListBox();
            this.SuspendLayout();
            // 
            // texturesList
            // 
            this.texturesList.Dock = System.Windows.Forms.DockStyle.Fill;
            this.texturesList.FormattingEnabled = true;
            this.texturesList.Location = new System.Drawing.Point(0, 0);
            this.texturesList.Name = "texturesList";
            this.texturesList.Size = new System.Drawing.Size(240, 322);
            this.texturesList.TabIndex = 0;
            this.texturesList.DoubleClick += new System.EventHandler(this.texturesList_DoubleClick);
            // 
            // TexturePickerForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(240, 322);
            this.Controls.Add(this.texturesList);
            this.MinimumSize = new System.Drawing.Size(256, 361);
            this.Name = "TexturePickerForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Choose Texture";
            this.ResumeLayout(false);

        }

        #endregion

        public System.Windows.Forms.ListBox texturesList;
    }
}