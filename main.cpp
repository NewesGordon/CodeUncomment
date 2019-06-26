#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>

int main(int argc, char *argv[])//.exe old0.txt old1.txt ... new.txt
{
    QCoreApplication a(argc, argv);

    if(argc < 3){
        qDebug() << "too less paras.";
        return a.exec();
    }
    QList<QFile*> oldFileList;//待读取文件列表
    for(int i=1; i<argc-1; i++){
        QFile *oldFile = new QFile(argv[i]);//待修改文件
        oldFileList.append(oldFile);
    }
    QFile newFile(argv[argc-1]);//修改后保存的新文件

    newFile.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Append);//打开新文件
    QTextStream out(&newFile);//定义写文件流

    int count = 0;//行计数

    //循环读取文件
    for(int i=0; i<oldFileList.length(); i++){
        oldFileList[i]->open(QIODevice::ReadOnly | QIODevice::Text);//打开旧文件
        QString line;//缓存每一行读取
        //循环读取新的行
        while(!oldFileList[i]->atEnd()){
            line = oldFileList[i]->readLine();//读取新一行
            if(line != "\n"){//忽略空行
                line = line.left(line.indexOf("//")).simplified();
                if(line != ""){//删除注释后，忽略空行
                    if(line.contains("\n"))
                        out << line;//写入新行
                    else
                        out << line << endl;//写入新行
                    qDebug() << "Line No." << ++count;
                }
            }
        }
        oldFileList[i]->close();
    }
    //关闭文件
    newFile.close();

    //释放内存
    for(int i=0; i<oldFileList.length(); i++){
        delete oldFileList.at(i);
    }
    oldFileList.clear();

    qDebug() << "---------Done!----------";
    qDebug() << "total:" << count << "lines.";

    return a.exec();
}
