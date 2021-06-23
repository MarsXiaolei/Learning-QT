#include <QCoreApplication>
#include <QQueue>
#include <QDebug>

////////////////////////////////////////////////////////////////
/// @brief  QQueue使用示例
/// @note   继承自QList
/// @note   队列是先进先出(FIFO)结构
////////////////////////////////////////////////////////////////

struct Score
{
public:
    Score(){}           //! 需要手动编写默认构造函数
    Score(int chinese,int math,int english)
    {
        m_chinese = chinese;
        m_math = math;
        m_english = english;
    }

    /// 结构体数据
    int m_chinese = 0;
    int m_math = 0;
    int m_english = 0;
};

struct Student
{
public:
    Student(){}
    Student(QString name,QString gender,int age,Score score)
    {
        m_name = name;
        m_gender = gender;
        m_age = age;
        m_score = score;
    }

    /// 重载 == 操作符
    bool operator ==(Student &t)
    {
        if (sizeof(this) != sizeof(t))
        {
            return false;
        }

        if(this->m_name != t.m_name)
        {
            return false;
        }

        if(this->m_gender != t.m_gender)
        {
            return false;
        }

        if(this->m_age != t.m_age)
        {
            return false;
        }

        if(this->m_score.m_chinese != t.m_score.m_chinese)
        {
            return false;
        }

        if(this->m_score.m_math != t.m_score.m_math)
        {
            return false;
        }

        if(this->m_score.m_english != t.m_score.m_english)
        {
            return false;
        }

        return true;
    }

    /// 重载 << 操作符 打印结构体
    friend QDebug operator << (QDebug debug, const Student &t)
    {
        QString info = QString("name =%1 gender =%2 age =%3 chinese =%4 math =%5 english =%6")
                .arg(t.m_name).arg(t.m_gender).arg(t.m_age)
                .arg(t.m_score.m_chinese).arg(t.m_score.m_math).arg(t.m_score.m_english);
        debug << info;
        return debug;
    }

    /// 结构体数据
    QString m_name = "";
    QString m_gender = "";
    int m_age = 0;
    Score m_score;
};


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /// 初始化结构体
    Score scoreA(100,87,90);
    Student studentA("张三","male",15,scoreA);
    Score scoreB(100,87,90);
    Student studentB("李四","female",13,scoreB);
    Score scoreC(100,87,90);
    Student studentC("王二","male",15,scoreC);
    Score scoreD(100,87,90);
    Student studentD("麻子","female",16,scoreD);
    Score scoreE(100,87,90);
    Student studentE("燕十三","male",15,scoreE);

    /// 使用enqueue将项插入至队尾
    QQueue<Student> studentQueue;
    studentQueue.enqueue(studentA);
    studentQueue.enqueue(studentB);
    studentQueue.enqueue(studentC);
    studentQueue.enqueue(studentD);
    studentQueue.enqueue(studentE);

    qDebug().noquote()<<"\n队列Head :"<<studentQueue.head();

    qDebug().noquote()<<"";
    while (!studentQueue.isEmpty())
    {
        /// 删除队列中的头部项目并返回
        qDebug().noquote()<<studentQueue.dequeue();
    }

    return a.exec();
}
