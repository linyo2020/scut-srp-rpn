#ifndef PTNET_H
#define PTNET_H
#include"place.h"
#include"arc.h"
#include"transition.h"

class PTNet: public QObject
{
public:
    PTNet();
    PTNet(PTNet&mynet);
    QList<Place*>PlaceList;
    QList<Transition*>TransitionList;
    //contained in place and transition
    QList<Arc*>ArcList;

    //componentToXml()不太清楚如何处理，需不要需要把add函数放进这里面

    //两种List数据流获取
    //在petritabwidget中setComponent（）函数，直接进行xml文件的读取。需要ui的配合，用户在画完控件后必须进行保存。这样就变为读取xml的问题了。
    //利用defs中的page
    //设想方案：
    //------------------------------------------------------
    //用户完成控件的绘制后必须进行保存，页面内容被存储为xml，控件库就维护这些xml文件。
    //仿真前的绘制阶段:
    //当用户想要利用控件库中控件进行绘制模型时，用户点击控件库列表中的某一项,随后系统读取xml文件中的内容,将内容呈现在绘制界面上.
    //用户在绘制阶段只能手动处理不同控件之间的连接关系(即手动将创建的控件连如模型).绘制完成后点击仿真,将用户绘制的模型也视为控件.
    //仿真时:
    //系统遍历规则库,由某个类调用规则库中指定的操作如复制.
    //该复制任务会被指派到具体的某个控件中,被指定的控件执行复制操作.
    //复制操作(复制的控件已经被保存在控件库中)：
    //系统将控件库的该控件重新读入到系统中,并且被复制的控件与其复制体之间的联系关系由某个类来进行指定(如merge连接关系)
    //由于不同控件之间存在关系(关系由规则库调用),在处理时,应当由某个类应当处理这个关系(如merge)


    void AddPlace(Place *myplace);
    void AddTransition(Transition *mytrans);
    void AddArc(Arc *myarc);
    void deletePlace(Place *myplace);
    void deleteTransition(Transition *mytrans);

};

#endif // PTNET_H
