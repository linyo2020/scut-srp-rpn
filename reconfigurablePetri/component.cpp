#include "component.h"

Component::Component()
{

}

QString Component::getLabel() const
{
    return label;
}

void Component::setLabel(const QString &value)
{
    label = value;
}

Component Component::merge(PTNet otherNet, QString thisNet_port,QString otherNet_port)
{
    int mynet_inputport;
    int mynet_outputport;
    int otherNet_inputport;
    int otherNet_outputport;

    for(int i=0;i<mynet.PlaceList.size();i++)
    {
        if(mynet.PlaceList[i]->isInputPort())
        {
            mynet_inputport=i;
        }
        else if(mynet.PlaceList[i]->isOutputPort())
        {
            mynet_outputport=i;
        }
    }

    for(int i=0;i<otherNet.PlaceList.size();i++)
    {
        if(otherNet.PlaceList[i]->isInputPort())
        {
            otherNet_inputport=i;
        }
        else if(otherNet.PlaceList[i]->isOutputPort())
        {
            otherNet_outputport=i;
        }
    }


        //todo
        //1.无法将不同组件合并为一个组件，仅是单纯的将不同的端口以变迁为桥梁连接在了一起。
        //！2.不同端口连接后，这两个库所的属性是否仍为端口？
        //！3.针对撤销操作可能需要有代码结构上的改变
        //4.作为不同端口的中间桥梁的变迁的id值需要唯一吗？(目前的id值可能不唯一)
        //5.一个端口是否可以同时连接多个端口（与2可能产生冲突）
        //6.仅做了place之间的连接
        if(thisNet_port=="outputPort")
        {
            Transition* trans=new Transition("merge"+otherNet.PlaceList[mynet_outputport]->getId());
            if(otherNet_port=="inputPort")
            {
                //outputoprt connect inputport

               Arc *my_arc1=new Arc(this->mynet.PlaceList[mynet_outputport],this->mynet.PlaceList[mynet_outputport]->getId(),trans,trans->getId(),this->mynet.PlaceList[mynet_outputport]->getId()+"_"+trans->getId(),1);

               Arc *my_arc2=new Arc(trans,trans->getId(),otherNet.PlaceList[otherNet_inputport],otherNet.PlaceList[otherNet_inputport]->getId(),trans->getId()+"_"+otherNet.PlaceList[otherNet_inputport]->getId(),1);

               trans->addInputArc(my_arc1);
               trans->addOutputArc(my_arc2);
               this->mynet.PlaceList[mynet_outputport]->addOutputArc(my_arc1);
               otherNet.PlaceList[otherNet_inputport]->addInputArc(my_arc2);

            }
            else if(otherNet_port=="outputPort")
            {


                Arc *my_arc1=new Arc(this->mynet.PlaceList[mynet_outputport],this->mynet.PlaceList[mynet_outputport]->getId(),trans,trans->getId(),null,this->mynet.PlaceList[mynet_outputport]->getId()+"_"+trans->getId(),1);

                Arc *my_arc2=new Arc(trans,trans->getId(),otherNet.PlaceList[otherNet_outputport],otherNet.PlaceList[otherNet_outputport]->getId(),null,trans->getId()+"_"+otherNet.PlaceList[otherNet_outputport]->getId(),1);

                trans->addInputArc(my_arc1);
                trans->addOutputArc(my_arc2);
                this->mynet.PlaceList[mynet_outputport]->addOutputArc(my_arc1);
                otherNet.PlaceList[otherNet_outputport]->addInputArc(my_arc2);

            }
        }

        else if(thisNet_port=="inputPort")
        {
            Transition* trans=new Transition("merge"+otherNet.PlaceList[mynet_outputport]->getId());
            if(otherNet_port=="inputPort")
            {
                //outputoprt connect inputport

               Arc *my_arc1=new Arc(this->mynet.PlaceList[mynet_inputport],this->mynet.PlaceList[mynet_inputport]->getId(),trans,trans->getId(),this->mynet.PlaceList[mynet_inputport]->getId()+"_"+trans->getId(),1);

               Arc *my_arc2=new Arc(trans,trans->getId(),otherNet.PlaceList[otherNet_inputport],otherNet.PlaceList[otherNet_inputport]->getId(),trans->getId()+"_"+otherNet.PlaceList[otherNet_inputport]->getId(),1);

               trans->addInputArc(my_arc1);
               trans->addOutputArc(my_arc2);
               this->mynet.PlaceList[mynet_inputport]->addOutputArc(my_arc1);
               otherNet.PlaceList[otherNet_inputport]->addInputArc(my_arc2);

            }
            else if(otherNet_port=="outputPort")
            {


                Arc *my_arc1=new Arc(this->mynet.PlaceList[mynet_inputport],this->mynet.PlaceList[mynet_inputport]->getId(),trans,trans->getId(),null,this->mynet.PlaceList[mynet_inputport]->getId()+"_"+trans->getId(),1);

                Arc *my_arc2=new Arc(trans,trans->getId(),otherNet.PlaceList[otherNet_outputport],otherNet.PlaceList[otherNet_outputport]->getId(),null,trans->getId()+"_"+otherNet.PlaceList[otherNet_outputport]->getId(),1);

                trans->addInputArc(my_arc1);
                trans->addOutputArc(my_arc2);
                this->mynet.PlaceList[mynet_inputport]->addOutputArc(my_arc1);
                otherNet.PlaceList[otherNet_outputport]->addInputArc(my_arc2);

            }
        }

}


int Component::getComponent_type() const
{
    return Component_type;
}

void Component::setComponent_type(int value)
{
    Component_type = value;
}