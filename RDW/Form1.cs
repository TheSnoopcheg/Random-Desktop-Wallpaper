namespace RDW
{
    public partial class Form1 : Form
    {
        string path = @"path.txt";
        public Form1()
        {
            InitializeComponent();

            getCurrentPath();

            button1.Click += button1_Click;
            button2.Click += button2_Click;
        }

        void button1_Click(object sender, EventArgs e)
        {
            if (folderBrowserDialog1.ShowDialog() == DialogResult.OK)
            {
                textBox1.Text = folderBrowserDialog1.SelectedPath;
            }
        }
        void button2_Click(object sender, EventArgs e)
        {
            System.IO.File.WriteAllText(path, textBox1.Text);
            label1.Text = "Saved";
        }
        async Task getCurrentPath()
        {
            using (StreamReader reader = new StreamReader(path))
            {
                textBox1.Text = await reader.ReadToEndAsync();
            }
        }
    }
}