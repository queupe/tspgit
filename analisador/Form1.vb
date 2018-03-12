Public Class Form1
    Inherits System.Windows.Forms.Form

#Region " Windows Form Designer generated code "

    Public Sub New()
        MyBase.New()

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        'Add any initialization after the InitializeComponent() call

    End Sub

    'Form overrides dispose to clean up the component list.
    Protected Overloads Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing Then
            If Not (components Is Nothing) Then
                components.Dispose()
            End If
        End If
        MyBase.Dispose(disposing)
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    Friend WithEvents TextBox1 As System.Windows.Forms.TextBox
    Friend WithEvents Button1 As System.Windows.Forms.Button
    Friend WithEvents Button2 As System.Windows.Forms.Button
    Friend WithEvents FolderBrowserDialog1 As System.Windows.Forms.FolderBrowserDialog
    Friend WithEvents TextBox2 As System.Windows.Forms.TextBox
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Button3 As System.Windows.Forms.Button
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents NumericUpDown1 As System.Windows.Forms.NumericUpDown
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.TextBox1 = New System.Windows.Forms.TextBox
        Me.Button1 = New System.Windows.Forms.Button
        Me.Button2 = New System.Windows.Forms.Button
        Me.FolderBrowserDialog1 = New System.Windows.Forms.FolderBrowserDialog
        Me.TextBox2 = New System.Windows.Forms.TextBox
        Me.Label1 = New System.Windows.Forms.Label
        Me.Button3 = New System.Windows.Forms.Button
        Me.Label2 = New System.Windows.Forms.Label
        Me.NumericUpDown1 = New System.Windows.Forms.NumericUpDown
        CType(Me.NumericUpDown1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'TextBox1
        '
        Me.TextBox1.Location = New System.Drawing.Point(24, 32)
        Me.TextBox1.Name = "TextBox1"
        Me.TextBox1.ReadOnly = True
        Me.TextBox1.Size = New System.Drawing.Size(216, 20)
        Me.TextBox1.TabIndex = 0
        Me.TextBox1.Text = ""
        '
        'Button1
        '
        Me.Button1.Location = New System.Drawing.Point(24, 72)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(184, 24)
        Me.Button1.TabIndex = 1
        Me.Button1.Text = "OK"
        '
        'Button2
        '
        Me.Button2.Location = New System.Drawing.Point(248, 32)
        Me.Button2.Name = "Button2"
        Me.Button2.Size = New System.Drawing.Size(32, 24)
        Me.Button2.TabIndex = 2
        Me.Button2.Text = "dir"
        '
        'TextBox2
        '
        Me.TextBox2.Location = New System.Drawing.Point(32, 136)
        Me.TextBox2.Multiline = True
        Me.TextBox2.Name = "TextBox2"
        Me.TextBox2.ScrollBars = System.Windows.Forms.ScrollBars.Both
        Me.TextBox2.Size = New System.Drawing.Size(608, 104)
        Me.TextBox2.TabIndex = 3
        Me.TextBox2.Text = ""
        '
        'Label1
        '
        Me.Label1.Location = New System.Drawing.Point(232, 72)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(40, 24)
        Me.Label1.TabIndex = 4
        Me.Label1.Text = "Label1"
        '
        'Button3
        '
        Me.Button3.Location = New System.Drawing.Point(376, 80)
        Me.Button3.Name = "Button3"
        Me.Button3.Size = New System.Drawing.Size(216, 24)
        Me.Button3.TabIndex = 5
        Me.Button3.Text = "gerar config"
        '
        'Label2
        '
        Me.Label2.Location = New System.Drawing.Point(376, 48)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(144, 16)
        Me.Label2.TabIndex = 7
        Me.Label2.Text = "número de execuções"
        '
        'NumericUpDown1
        '
        Me.NumericUpDown1.Location = New System.Drawing.Point(544, 40)
        Me.NumericUpDown1.Name = "NumericUpDown1"
        Me.NumericUpDown1.Size = New System.Drawing.Size(32, 20)
        Me.NumericUpDown1.TabIndex = 8
        Me.NumericUpDown1.Value = New Decimal(New Integer() {1, 0, 0, 0})
        '
        'Form1
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(656, 261)
        Me.Controls.Add(Me.NumericUpDown1)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Button3)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.TextBox2)
        Me.Controls.Add(Me.Button2)
        Me.Controls.Add(Me.Button1)
        Me.Controls.Add(Me.TextBox1)
        Me.Name = "Form1"
        Me.Text = "Form1"
        CType(Me.NumericUpDown1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        FolderBrowserDialog1.ShowDialog()
        TextBox1.Text = FolderBrowserDialog1.SelectedPath
    End Sub

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        If TextBox1.Text = "" Then
            MsgBox("Diretorio vazio")
            Return
        End If

        Dim cont As Integer = 0
        Dim d As String = Dir(TextBox1.Text & "\*.*", FileAttribute.Archive)
        While (d <> "")
            Application.DoEvents()
            TextBox2.Text = TextBox2.Text & d & Chr(13) & Chr(10)
            analise(TextBox1.Text & "\" & d)
            cont = cont + 1
            Label1.Text = cont
            d = Dir()
        End While

        MsgBox("fim da execução. " & cont & " arquivos")
    End Sub

    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        TextBox1.Text = "D:\publico\programas\resultados tsp"
    End Sub

    Function analise(ByVal arquivo As String)

    End Function

    Private Sub Button3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button3.Click
        Dim i As Integer
        Dim j As Integer
        Dim arquivo As Short
        Dim cami As String

        For i = 0 To 14
            For j = 0 To 14
                arquivo = FreeFile()
                cami = TextBox1.Text & "\tspcofig_" & i & "_" & j & ".xml"
                FileOpen(arquivo, cami, OpenMode.Output)
                PrintLine(arquivo, "<?xml version=""1.0"" encoding=""UTF-8"" standalone=""no"" ?>")
                PrintLine(arquivo, "<configuracaoTSP>")
                PrintLine(arquivo, "")
                PrintLine(arquivo, "<name>tspconfig</name>")
                PrintLine(arquivo, "")
                PrintLine(arquivo, "<source>TSPLIB</source>")
                PrintLine(arquivo, "")
                PrintLine(arquivo, "<description>Configuração da programa de Algoritmo Genético</description>")
                PrintLine(arquivo, "")
                PrintLine(arquivo, "<integer>15</integer>")
                PrintLine(arquivo, "")
                PrintLine(arquivo, "<printParcial>1</printParcial>")
                PrintLine(arquivo, "<tamanhoPopulacao>200</tamanhoPopulacao>")
                PrintLine(arquivo, "<numGeracoes>300</numGeracoes>")
                PrintLine(arquivo, "<percentManipulacao>30</percentManipulacao>")
                PrintLine(arquivo, "<percentMutacao>20</percentMutacao>")
                PrintLine(arquivo, "<percentReducao>77</percentReducao>")
                PrintLine(arquivo, "<mutacao>" & i & "</mutacao>")
                PrintLine(arquivo, "<selIndMutacao>1</selIndMutacao>")
                PrintLine(arquivo, "<cruzamento>" & j & "</cruzamento>")
                PrintLine(arquivo, "<numExec>" & NumericUpDown1.Value & "</numExec>")
                PrintLine(arquivo, "<roleta>0</roleta>")
                PrintLine(arquivo, "<percentElitismo>70</percentElitismo>")
                PrintLine(arquivo, "<ativaRecursivo>0</ativaRecursivo>")
                PrintLine(arquivo, "<percentMutacaoRecursiva>0</percentMutacaoRecursiva>")
                PrintLine(arquivo, "<timeout>4000</timeout>")
                PrintLine(arquivo, "</configuracaoTSP>")

                FileClose(arquivo)

            Next
        Next

    End Sub
End Class
