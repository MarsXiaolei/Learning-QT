#include <QCoreApplication>
#include <QMap>
#include <QDebug>
#include <QString>
#include <QList>

///////////////////////////////////////////////////////////////
/// @brief  QMap使用示例
/// @note   基于红黑树的字典
/// @note   存储(键、值)对，并提供与键关联的值的快速查找
/// @note   项目总是按键排序
/// @link   官方文档 https://doc.qt.io/qt-5/qmap.html
///////////////////////////////////////////////////////////////

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

class Teacher
{
public:
    Teacher(const QString &name,const QString &gender,const QString &course)
        :m_name(name),m_gender(gender),m_course(course)
    {

    }

    QString name()
    {
        return m_name;
    }

    QString gender()
    {
        return m_gender;
    }

    QString course()
    {
        return m_course;
    }

private:
    QString m_name;
    QString m_gender;
    QString m_course;
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

    /// 插入键值对 insert
    QMap<QString,Student> studentMap;
    studentMap.insert("000001",studentA);
    studentMap.insert("000002",studentB);
    studentMap.insert("000003",studentC);
    studentMap.insert("000004",studentD);
    studentMap.insert("000005",studentE);

    /// 插入键值对 []
//    studentMap["000001"] = studentA;
//    studentMap["000002"] = studentB;
//    studentMap["000003"] = studentC;
//    studentMap["000004"] = studentD;
//    studentMap["000005"] = studentE;

    //! 不推荐使用 按键查值 使用[]操作符
    Student student = studentMap["000001"];
    qDebug().noquote()<<"\n使用[]操作符查询 000001 :";
    qDebug().noquote()<<"name ="<<student.m_name
          <<"gender ="<<student.m_gender
         <<"age ="<<student.m_age
        <<"chinese ="<<student.m_score.m_chinese
       <<"math ="<<student.m_score.m_math
      <<"english ="<<student.m_score.m_english;

    //! 推荐使用 按键查值 使用value函数
    Student student_2 = studentMap.value("000001");
    qDebug().noquote()<<"\n使用value函数查询 000001 :";
    qDebug().noquote()<<"name ="<<student_2.m_name
          <<"gender ="<<student_2.m_gender
         <<"age ="<<student_2.m_age
        <<"chinese ="<<student_2.m_score.m_chinese
       <<"math ="<<student_2.m_score.m_math
      <<"english ="<<student_2.m_score.m_english;

    /// 查看是否包含000006，未包含则返回默认构造函数的值
    Student student_3;
    if(studentMap.contains("000006"))
    {
        student_3 = studentMap.value("000006");
    }
    qDebug().noquote()<<"\n查看是否包含 000006 :";
    qDebug().noquote()<<"name ="<<student_3.m_name
          <<"gender ="<<student_3.m_gender
         <<"age ="<<student_3.m_age
        <<"chinese ="<<student_3.m_score.m_chinese
       <<"math ="<<student_3.m_score.m_math
      <<"english ="<<student_3.m_score.m_english;

    qDebug()<<"count ="<<studentMap.count();


    //! 不推荐[] 键不相同会创建
    if(studentMap["000006"] == studentA)
    {
        qDebug()<<"Found studentA.";
    }

    //! 打印所有键 按升序遍历 使用迭代器
    QMap<QString,Student>::iterator iter= studentMap.begin();
    qDebug()<<"";
    while (iter != studentMap.end())
    {
        qDebug()<<"键 ="<<iter.key()<<"值 ="<<iter.value();
        ++iter;
    }

    //! 已存在的键调用insert()，之前的值将被擦除
    Score scoreF(60,60,60);
    Student studentF("朱重八","male",14,scoreF);
    studentMap.insert("000006",studentF);

    //! 打印所有键 按升序遍历 使用迭代器
    QMap<QString,Student>::iterator iter_2= studentMap.begin();
    qDebug()<<"";
    while (iter_2 != studentMap.end())
    {
        qDebug()<<"键 ="<<iter_2.key()<<"值 ="<<iter_2.value();
        ++iter_2;
    }

    /// 使用insertMulti为每个键存储多个值
    studentMap.clear();         ///< 先清空
    QMap<QString,Student> studentsMap;
    studentsMap.insertMulti("000001",studentA);
    studentsMap.insertMulti("000001",studentB);
    studentsMap.insertMulti("000001",studentC);
    studentsMap.insertMulti("000001",studentD);
    studentsMap.insertMulti("000001",studentE);
    studentsMap.insertMulti("000001",studentF);

    /// 使用values 查询键值
    QList<Student> stus_1 = studentsMap.values("000001");
    qDebug()<<"\n使用values 查询键000001 的值 stus_1.size()"<<stus_1.size();
    for(int i = 0; i < stus_1.size(); ++i)
    {
        qDebug()<<"值 ="<<stus_1.at(i);
    }


    //! 从映射(而不是键)中提取值
    qDebug()<<"";
    foreach (Student stu,studentsMap)
    {
        qDebug()<<"值 ="<<stu;
    }

    /// 使用迭代器 升序
    QMap<QString,Student>::iterator iter_3= studentsMap.begin();
    qDebug()<<"";
    while (iter_3 != studentsMap.end())
    {
        qDebug()<<"键 ="<<iter_3.key();
        qDebug()<<"值 ="<<iter_3.value();
        ++iter_3;
    }

    return a.exec();
}
