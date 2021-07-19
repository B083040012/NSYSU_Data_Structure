import tkinter
import tkinter.filedialog
import tkinter.messagebox
import os

window=tkinter.Tk()
window.geometry("1080x720")
window.maxsize(1920,1080)
window.title("Compress/Uncompress Application")
window['bg'] = '#303030'

files=()
filenames=tkinter.StringVar()

def Select_Files():
    global files
    files=tkinter.filedialog.askopenfilenames(initialdir='D:/C-Program/Data_Structure/Assignment/8/',title='Choose file')
    tmpfiles=[]
    for i in files:
        if(len(i)>=60):
            i=i[0:20]+'...'+i[-15:0]
        tmpfiles.append(i)
    filestr=' '.join(tmpfiles)
    print(filestr)
    filenames.set(filestr)

def Compress_File():
    global files
    filename = tkinter.filedialog.asksaveasfilename(initialdir='D:/C-Program/Data_Structure/Assignment/8/',title = '儲存檔案',filetypes = (('txt 檔案','*.txt'),('所有檔案','*.*')))
    for single_file in files:
        command='   hw8_b083040012.exe -c -i '+single_file+' -o '+filename
        print(command)
        os.system(command)
    tkinter.messagebox.showinfo(title = '操作結果',message = '壓縮成功：' + filename)

btnadd = tkinter.Button(window,text = 'Select File',bg = 'yellow',bd = 0.5,fg = 'black',command = Select_Files)
btnadd.place(x = 100,y = 70,width = '80',height = 30)

btnadd = tkinter.Button(window,text = 'Compress file',bg = 'yellow',bd = 0.5,fg = 'black',command = Compress_File)
btnadd.place(x = 300,y = 70,width = '80',height = 30)

label = tkinter.Label(window,bg = '#F2F2F2',textvariable = filenames,anchor = 'nw',justify = 'left')
label.place(x= 5,y = 115,width = '690',height = '370')

window.mainloop()   