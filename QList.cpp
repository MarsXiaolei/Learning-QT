#include <QCoreApplication>
#include <QList>
#include <QString>
#include <QDebug>

/////////////////////////////////////////////////////////////////////////////
/// @note   QList在列表的两端插入和删除项是非常快的
/// @note   因为QList在其内部缓冲区的两端预先分配了额外的空间，以允许在列表的两端快速增长
/// @note   下标越界会导致异常，在调用其他成员函数之前调用isEmpty()
/// @link   官方文档：https://doc.qt.io/qt-5/qlist.html
/////////////////////////////////////////////////////////////////////////////

struct Student
{
public:
    Student(QString id,QString name,QString gender,int age)
    {
        m_id = id;
        m_name = name;
        m_gender = gender;
        m_age = age;
    }

    QString m_id;
    QString m_name;
    QString m_gender;
    int m_age;
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

    QList<Student> list;
    Student studentA("001","张三","male",15);
    Student studentB("002","李四","female",13);
    Student studentC("003","王二","male",15);
    Student studentD("004","麻子","female",16);
    Student studentE("005","燕十三","male",15);

    /// 使用操作符<<插入
    //list<<studentA<<studentB<<studentC<<studentD<<studentE;

    /// 使用push_back添加至尾部
//    list.push_back(studentA);
//    list.push_back(studentB);
//    list.push_back(studentC);
//    list.push_back(studentD);
//    list.push_back(studentE);

    /// 使用push_front添加至头部
    list.push_front(studentA);
    list.push_front(studentB);
    list.push_front(studentC);
    list.push_front(studentD);
    list.push_front(studentE);

    /// 使用下标遍历，at比[]快
//    for(int i = 0;i < list.size();++i)
//    {
//        qDebug().noquote()<<"id ="<<list.at(i).m_id
//               <<"name ="<<list.at(i).m_name
//              <<"gender ="<<list.at(i).m_gender
//             <<"age ="<<list.at(i).m_age;
//    }

    /// 迭代器遍历
//    QList<Student>::iterator iter = list.begin();
//    for(iter = list.begin();iter != list.end();++iter)
//    {
//        qDebug().noquote()<<"id ="<<(*iter).m_id
//               <<"name ="<<(*iter).m_name
//              <<"gender ="<<(*iter).m_gender
//             <<"age ="<<(*iter).m_age;
//    }

    /// 使用foreach遍历
    foreach (auto student, list)
    {
        qDebug().noquote()<<"id ="<<student.m_id
               <<"name ="<<student.m_name
              <<"gender ="<<student.m_gender
             <<"age ="<<student.m_age;
    }

    /// 动态分配内存
    Teacher *teacherA = new Teacher("青龙","male","english");
    Teacher *teacherB = new Teacher("白虎","female","chinese");
    Teacher *teacherC = new Teacher("朱雀","female","math");
    Teacher *teacherD = new Teacher("玄武","male","music");

    QList<Teacher **> list_2;
    list_2<<&teacherA<<&teacherB<<&teacherC<<&teacherD;

    /// 使用foreach遍历
    foreach (auto teacher, list_2)
    {
        qDebug().noquote()<<"name ="<<(*teacher)->name()
               <<"gender ="<<(*teacher)->gender()
              <<"m_course ="<<(*teacher)->course();
    }

    /// 查询列表项目位置
    int index = list_2.indexOf((&teacherB));
    if(index != -1)
    {
        qDebug().noquote()<<"查询teacherB:";
        qDebug().noquote()<<"name ="<<teacherB->name()
               <<"gender ="<<teacherB->gender()
              <<"m_course ="<<teacherB->course();
    }

    /// 查询某个项目出现的次数
    int num = list_2.count((&teacherB));
    qDebug().noquote()<<teacherB->name()<<"出现的次数 ="<<num;

    /// 列表中项目的数量
    int count = list_2.count();
    qDebug().noquote()<<"count ="<<count;

    /// 全部删除
    while(!list_2.isEmpty())
    {
        //! 移除第一个，只删除了列表项，但teacherA分配的内存还在
        Teacher **teacher = list_2.takeFirst();
        qDebug().noquote()<<"当前移除的是 :"<<(*teacher)->name();
        
        delete *teacher;
        *teacher = nullptr;     //! delete之后需要赋为空

        /// 删除最后一个
        //list_2.takeLast();
    }

    /// 手动释放内存
    if(teacherA != nullptr)
    {
        qDebug().noquote()<<"teacherA != NULL."<<teacherA;
        delete teacherA;
        teacherA = nullptr;
        qDebug().noquote()<<"finish delete teacherA."<<teacherA;
    }

    /// 手动释放内存
    if(teacherB != nullptr)
    {
        qDebug().noquote()<<"teacherB != NULL."<<teacherB;
        delete teacherB;
        teacherB = nullptr;
        qDebug().noquote()<<"finish delete teacherB."<<teacherB;
    }

    /// 手动释放内存
    if(teacherC != nullptr)
    {
        qDebug().noquote()<<"teacherC != NULL."<<teacherC;
        delete teacherC;
        teacherC = nullptr;
        qDebug().noquote()<<"finish delete teacherC."<<teacherC;
    }

    /// 手动释放内存
    if(teacherD != nullptr)
    {
        qDebug().noquote()<<"teacherD != NULL."<<teacherD;
        delete teacherD;
        teacherD = nullptr;
        qDebug().noquote()<<"finish delete teacherD."<<teacherD;
    }

    return a.exec();
}
