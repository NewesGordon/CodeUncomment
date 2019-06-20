#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>

int main(int argc, char *argv[])//.exe old.txt new.txt
{
    QCoreApplication a(argc, argv);

    QFile oldFile(argv[1]);//待修改文件
    QFile newFile(argv[2]);//修改后保存的新文件

    newFile.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Append);//打开新文件
    QTextStream out(&newFile);//定义写文件流

    oldFile.open(QIODevice::ReadOnly | QIODevice::Text);//打开旧文件
    QString line;//缓存每一行读取
    int count = 0;
    //循环读取新的行
    while(!oldFile.atEnd()){
        line = oldFile.readLine();//读取新一行
        if(line != "\n"){//忽略空行
            line = line.left(line.indexOf("//")).simplified();
            if(line != ""){//删除注释后，忽略空行
                if(line.contains("\n"))
                    out << line;//写入新行
                else
                    out << line << endl;//写入新行
                qDebug() << "第" << ++count << "行";
            }
        }
    }

    oldFile.close();
    newFile.close();

    qDebug() << "---------Done!----------";
    qDebug() << "共" << count << "行代码.";

    return a.exec();
}
