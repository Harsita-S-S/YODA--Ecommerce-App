#include "productinfo.h"
#include <qlabel.h>

ProductInfo::ProductInfo(Inventory &inventory,Cart &finalcart, string productname, QWidget *parent) : QWidget(parent),productName(productname),finalCart(finalcart) {
    this->inventory=inventory;
    setGeometry(QRect(50, 50, 400, 300));
    vector<Product*> products;
    products=inventory.getAllProducts();
    setFixedSize(400,250);
    setWindowTitle("Product Information");
    QWidget *container = new QWidget(this);
    container->setFixedSize(400,250);
    container->setStyleSheet("QWidget { border: 2px solid white; background-color: #333; }");
    int num=0;
    for(int i=0;i<products.size();i++)
    {
        if(products[i]->getName()==productName)
        {
            num=i;
        }
    }
    num++;
    QLabel *name = new QLabel(QString::fromStdString(std::string(products[num - 1]->getName())), container);
    name->setGeometry(8,10,385,25);
    name->setStyleSheet("color: white; border:none");
    if(products[num-1]->getCategory()=="Furniture")
    {
        QLabel *desc=new QLabel(QString::fromStdString(products[num-1]->getDetails())+
                                "\nWoodType : "+QString::fromStdString(products[num-1]->getWoodType())+
                                "\nType : "+QString::fromStdString(products[num-1]->getType())+
                                "\nSpecifications : "+QString::fromStdString(products[num-1]->getSpecifications()),container);
        desc->setGeometry(8,50,385,125);
        desc->setWordWrap(true);
        desc->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    }
    if(products[num-1]->getCategory()=="Clothes")
    {
        QLabel *desc=new QLabel(QString::fromStdString(products[num-1]->getDetails())+
                                      "\nSize : "+QString::fromStdString(products[num-1]->getSize())+
                                      "\nMaterial : "+QString::fromStdString(products[num-1]->getMaterial())+
                                      "\nType : "+QString::fromStdString(products[num-1]->getType())+
                                      "\nBrand : "+QString::fromStdString(products[num-1]->getBrand()),container);

        desc->setGeometry(8,50,385,125);
        desc->setWordWrap(true);
        desc->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    }
    if(products[num-1]->getCategory()=="Electronics")
    {
        QLabel *desc=new QLabel(QString::fromStdString(products[num-1]->getDetails())+
                                      "\nCompany : "+QString::fromStdString(products[num-1]->getCompany())+
                                      "\nType : "+QString::fromStdString(products[num-1]->getType())+
                                      "\nSpecifications : "+QString::fromStdString(products[num-1]->getSpecifications()),container);


        desc->setGeometry(8,50,385,125);
        desc->setWordWrap(true);
        desc->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    }
    QLabel *price = new QLabel("Price  :       $  "+QString::number(products[num - 1]->getPrice()), container);
    price->setGeometry(8,190,125,25);
    price->setStyleSheet("color: white;padding-right:10px");
    cart=new QPushButton("ADD TO CART",container);
    cart->setGeometry(150,190,125,25);
    connect(cart,&QPushButton::clicked,this,[=]{cart->hide();cartClick(container,price,num);});


    back_submit=new QPushButton("Back",container);
    back_submit->setGeometry(290,190,100,25);

    connect(back_submit,&QPushButton::clicked,this,[=]{back_submit_click(num);});
}
void ProductInfo::cartClick(QWidget *container, QLabel *price, int num)
{
    plus = new QPushButton("+",container);
    plus->setGeometry(160,190,20,25);
    plus->show();
    quantity = new QLineEdit(container);
    quantity->setGeometry(190,190,40,25);
    quantity->setText("1");
    quantity->show();
    quantity->setAlignment(Qt::AlignCenter);

    back_submit->setText("Submit");

    minus = new QPushButton("-",container);
    minus->setGeometry(240,190,20,25);
    minus->show();
    connect(plus,&QPushButton::clicked,this,[=]{plusClick(quantity,price,num);});
    connect(minus,&QPushButton::clicked,this,[=]{minusClick(quantity,price,num);});
}
void ProductInfo::plusClick(QLineEdit* quant, QLabel *price, int num)
{
    vector<Product*> products;
    products=inventory.getAllProducts();
    int quantityValue=quant->text().toInt();
    quant->setText(QString::number(quantityValue+1));
    price->setText("Price  :       $  "+QString::number(products[num - 1]->getPrice()*(quantityValue+1)));
    back_submit->setText("Submit");
}
void ProductInfo::minusClick(QLineEdit* quant, QLabel *price, int num)
{
    vector<Product*> product;
    product=inventory.getAllProducts();
    int quantityValue=quant->text().toInt();
    if(quantityValue-1==0)
    {
        quant->setText(QString::number(quantityValue-1));
        back_submit->setText("Back");
    }
    if(quantityValue-1>0)
    {
        quant->setText(QString::number(quantityValue-1));
        price->setText("Price  :       $  "+QString::number(product[num - 1]->getPrice()*(quantityValue-1)));
    }
}
void ProductInfo::back_submit_click(int num)
{
    vector<Product*> product;
    product=inventory.getAllProducts();
    if(back_submit->text().toStdString()=="Back")
    {
        this->close();
    }
    else
    {
        finalCart.addProduct(*product[num-1],quantity->text().toInt());
        this->close();
    }

}
