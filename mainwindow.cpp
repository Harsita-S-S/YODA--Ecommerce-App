#include "mainwindow.h"
#include "cartviewwindow.h"
#include "clothes.h"
#include "electronics.h"
#include "furniture.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QPixmap>
#include <QDir>
#include <QDebug>
#include <QTimer>
#include <QFont>
#include <QCheckBox>
#include <fstream>




MainWindow::MainWindow(User &user1,QWidget *parent) : QWidget(parent),user(user1) {
    setWindowTitle("Main Window");
    QLabel *welcome = new QLabel("You Ordered Delivery Assured",this) ;

    QFont normal;
    normal.setPointSize(30);
    welcome->setFont(normal);
    welcome->setGeometry(355,40,600,60);
    QScrollArea *scrollArea=new QScrollArea(this);
    scrollArea->setGeometry(200+350,100+50+50,600,500);
    scrollArea->setWidgetResizable(true);


    QWidget *container = new QWidget();
    container->setFixedSize(585,1600);

    container->setStyleSheet("QWidget { border:2px solid white; background-color:#333; }");


    populateInventory(inventory);
    vector<Product*> product;
    product=inventory.getAllProducts();
    std::vector<QPushButton*> items(product.size());
    for(int i=0;i<product.size();i++){

        items[i] = new QPushButton(QString::number(i+1) + ". " + QString::fromStdString(product[i]->getName()), container);
        items[i]->setStyleSheet("color:white; font-size:14px; text-align: left; padding-left: 10px;");
        items[i]->setGeometry(30,50+(i*30),200,25);
        connect(items[i],&QPushButton::clicked,this,[=]{productClick(product[i]->getName());});

        QLabel *pricevalue = new QLabel("$ "+QString::number(product[i]->getPrice()),container);
        pricevalue->setGeometry(400,50+(i*30),50,25);
        pricevalue->setStyleSheet("border:none");
    }
    QLabel *productName = new QLabel("Product Name",container);
    productName->setGeometry(30,20,80,25);
    productName->setStyleSheet("border:none");
    productName->setObjectName("keep");
    QLabel *priceVal = new QLabel("Price",container);
    priceVal->setGeometry(400,20,50,25);
    priceVal->setStyleSheet("border:none");
    priceVal->setObjectName("keep");

    /*fstream fh;
    QString path=QDir::currentPath()+"/data.bin";

    fh.open(path.toStdString(), std::ios::out | std::ios::binary);
    for (const Product& p : product) {
        fh.write((char*)&p, sizeof(p));
    }
    fh.close();
    vector<Product> product1;
    ifstream fh1;
    //QString path=QDir::currentPath()+"/data.bin";
    fh1.open(path.toStdString(), std::ios::in| std::ios::binary);
    while (fh1.peek() != EOF) {
        Product p;
        fh1.read((char*)&p, sizeof(p));
        if (fh1.gcount() == sizeof(Product)) {
            product1.push_back(p);
        }
    }
    fh1.close();


    qDebug() << "File location:" << QDir::currentPath();
    for(int i=0;i<10;i++)
    {
        cout << product1[i];
    }

    fh1.close();*/
    scrollArea->setWidget(container);
    QLabel *search =new QLabel("Search : -",this);
    search->setGeometry(200+350,50+50+50,50,30);
    search->show();
    search_bar = new QLineEdit(this);
    search_bar->setGeometry(250+350,50+50+50,350,30);
    search_bar->show();
    connect(search_bar,&QLineEdit::selectionChanged,this,[=](){search_bar->clear();});

    connect(search_bar,&QLineEdit::returnPressed,this,[=]{searching(container);});

    clear = new QPushButton("Clear",this);
    clear->setGeometry(600+350+3,50+50+50,65,30);
    clear->hide();
    connect(clear,&QPushButton::clicked,this,[=]{clearing(container);});
    productinfo = nullptr;
    QLabel *productInformation = new QLabel("Product Information",this);
    productInformation->setGeometry(50,360+50,150,25);
    normal.setPointSize(12);
    productInformation->setFont(normal);
    QWidget *container1 = new QWidget(this);
    container1->setGeometry(50,400+50,400,250);
    container1->setStyleSheet("QWidget { border:2px solid white; background-color:#333; }");
    container1->show();
    QLabel *noInfo = new QLabel("Click a Product to show its information",container1);
    noInfo->setStyleSheet("border:none");
    noInfo->setWordWrap(true);
    noInfo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    normal.setPointSize(16);
    noInfo->setGeometry(50,80,250,100);
    noInfo->setFont(normal);

    QWidget *filter = new QWidget(this);
    filter->setGeometry(50,200,400,200);
    filter->setStyleSheet("QWidget { border:2px solid white; background-color:#333; }");
    filter->show();
    QLabel *filters = new QLabel("Filters",this);
    filters->setGeometry(50,150,50,30);
    normal.setPointSize(12);
    filters->setFont(normal);
    filters->setStyleSheet("border:none");

    QLabel *price = new QLabel("Price",filter);
    price->setGeometry(20,20,50,30);
    normal.setPointSize(16);
    price->setFont(normal);
    price->setStyleSheet("border:none");

    lowToHigh = new QRadioButton("Low To High",filter);
    highToLow = new QRadioButton("High to Low",filter);
    lowToHigh->setGeometry(30,70,100,30);
    highToLow->setGeometry(30,70+40,100,30);
    lowToHigh->setStyleSheet("border:none");
    highToLow->setStyleSheet("border:none");
    group = new QButtonGroup(filter);
    group->addButton(lowToHigh);
    group->addButton(highToLow);
    connect(group,&QButtonGroup::buttonClicked,this,[=](QAbstractButton* button){filteringPrice(button,container,product);});

    QLabel *furn = new QLabel("Category",filter);
    furn->setGeometry(200,20,120,30);
    furn->setFont(normal);
    furn->setStyleSheet("border:none");
    categories = new QButtonGroup(filter);
    categories->setExclusive(true);
    furniture=new QCheckBox("Furniture",filter);
    furniture->setChecked(false);
    furniture->setGeometry(210,70,120,30);
    furniture->setStyleSheet("border:none");
    electronics=new QCheckBox("Electronics",filter);
    electronics->setChecked(false);
    electronics->setGeometry(210,70+40,120,30);
    electronics->setStyleSheet("border:none");
    clothes=new QCheckBox("Clothes",filter);
    clothes->setChecked(false);
    clothes->setGeometry(210,70+80,120,30);
    clothes->setStyleSheet("border:none");
    categories->addButton(furniture);
    categories->addButton(electronics);
    categories->addButton(clothes);
    connect(furniture, &QCheckBox::checkStateChanged, this, [=](int state) { filteringCategory(state, "Furniture", container); });
    connect(electronics, &QCheckBox::checkStateChanged, this, [=](int state) { filteringCategory(state, "Electronics", container); });
    connect(clothes, &QCheckBox::checkStateChanged, this, [=](int state) { filteringCategory(state, "Clothes", container); });
    viewCartButton = new QPushButton("View Cart",this);
    viewCartButton->setGeometry(600+350+50+20,50+50+50,100,30);
    connect(viewCartButton,&QPushButton::clicked,this,&MainWindow::viewingCart);

}

void MainWindow::viewingCart()
{
    user.setCart(cart);
    cartviewing = new CartViewWindow(&cart);
    cartviewing->show();
}
void MainWindow::filteringPrice(QAbstractButton* button, QWidget *container, std::vector<Product*> products)
{
    vector<Product*> product1;

    vector<Product*> product;
    product1=inventory.getAllProducts();
    for(QObject *child : container->children()) {
        QLabel *label = qobject_cast<QLabel*>(child);
        if(label && (label->objectName()=="keep")) continue;

        QPushButton *button=qobject_cast<QPushButton*>(child);
        if(button){
            QString btnText=button->text();
            QStringList parts=btnText.split(". ");
            QString productName=parts[1];
            for(int i=0;i<product1.size();i++) {
                if(QString::fromStdString(product1[i]->getName())==productName) {
                    qDebug() << productName;
                    product.push_back(product1[i]);
                    break;
                }
            }
        }
        QWidget *widget = qobject_cast<QWidget*>(child);
        if(widget) widget->deleteLater();
    }
    if(products.size()<product.size())
    {
        product=products;
    }
    else{
    }
    for(int i=0;i<product.size()-1;i++)
    {
        for(int j=i+1;j<product.size();j++)
        {
            if(button==lowToHigh)
            {
                if(product[i]->getPrice()>product[j]->getPrice())
                {
                    Product *p=product[i];
                    product[i]=product[j];
                    product[j]=p;
                }
            }
            else
            {
                if(product[i]->getPrice()<product[j]->getPrice())
                {
                    Product *p=product[i];
                    product[i]=product[j];
                    product[j]=p;
                }
            }
        }
    }
    search_bar->clear();
    clear->show();
    std::vector<QPushButton*> searchedItems(product.size());
    int count=0;

    for(int i=0;i<product.size();i++)
    {
        searchedItems[count] = new QPushButton(QString::number(count+1) + ". " + QString::fromStdString(product[i]->getName()), container);
        searchedItems[count]->setStyleSheet("color:white; font-size:14px; text-align: left; padding-left: 10px;");
        searchedItems[count]->setGeometry(30,50+(count*30),200,25);
        searchedItems[count]->show();
        QLabel *pricevalue = new QLabel("$ "+QString::number(product[i]->getPrice()),container);
        pricevalue->setGeometry(400,50+(count*30),50,25);
        pricevalue->setStyleSheet("border:none");
        pricevalue->show();

        connect(searchedItems[count],&QPushButton::clicked,this,[=]{productClick(product[i]->getName());});
        count++;
    }

}



void MainWindow:: searching(QWidget *container)
{
    int flag=0;

    vector<Product*> product;
    product=inventory.getAllProducts();
    for(QObject *child : container->children()) {
        QLabel *label = qobject_cast<QLabel*>(child);
        if(label && (label->objectName()=="keep")) continue;

        QWidget *widget = qobject_cast<QWidget*>(child);
        if(widget) widget->deleteLater();
    }
    int count=0;

    for(int i=0;i<product.size();i++)
    {
        if((QString::fromStdString(std::string(product[i]->getName())).toLower()).contains(search_bar->text().toLower()) || search_bar->text().toLower().contains((QString::fromStdString(std::string(product[i]->getName())).toLower())))
        {
            count++;flag=1;
        }
    }
    std::vector<QPushButton*> searchedItems(count);
    count=0;
    for(int i=0;i<product.size();i++)
    {
        if((QString::fromStdString(std::string(product[i]->getName())).toLower()).contains(search_bar->text().toLower()) || search_bar->text().toLower().contains((QString::fromStdString(std::string(product[i]->getName())).toLower())))
        {
            searchedItems[count] = new QPushButton(QString::number(count+1) + ". " + QString::fromStdString(product[i]->getName()), container);
            searchedItems[count]->setStyleSheet("color:white; font-size:14px; text-align: left; padding-left: 10px;");
            searchedItems[count]->setGeometry(30,50+(count*30),200,25);
            searchedItems[count]->show();
            QLabel *pricevalue = new QLabel("$ "+QString::number(product[i]->getPrice()),container);
            pricevalue->setGeometry(400,50+(count*30),50,25);
            pricevalue->setStyleSheet("border:none");
            pricevalue->show();

            connect(searchedItems[count],&QPushButton::clicked,this,[=]{productClick(product[i]->getName());});
            count++;
        }
    }
    clear->show();

    if(flag!=1)
    {
        QLabel *nothing = new QLabel("No matching results found",container);
        nothing->setGeometry(100,100,200,25);
        nothing->show();
    }
}
void MainWindow::clearing(QWidget* container)
{
    for(QObject *child : container->children()) {
        QLabel *label = qobject_cast<QLabel*>(child);
        if(label && (label->objectName()=="keep")) continue;

        QWidget *widget = qobject_cast<QWidget*>(child);
        if(widget) widget->deleteLater();
    }
    clear->hide();
    vector<Product*> product;
    product=inventory.getAllProducts();
    std::vector<QPushButton*> items(product.size());
    for(int i=0;i<product.size();i++){

        items[i] = new QPushButton(QString::number(i+1) + ". " + QString::fromStdString(product[i]->getName()), container);
        items[i]->setStyleSheet("color:white; font-size:14px; text-align: left; padding-left: 10px;");
        items[i]->setGeometry(30,50+(i*30),200,25);
        connect(items[i],&QPushButton::clicked,this,[=]{productClick(product[i]->getName());});
        items[i]->show();
        QLabel *pricevalue = new QLabel("$ "+QString::number(product[i]->getPrice()),container);
        pricevalue->setGeometry(400,50+(i*30),50,25);
        pricevalue->setStyleSheet("border:none");
        pricevalue->show();
    }
    clearButtons();

}
void MainWindow::clearButtons()
{
    search_bar->clear();
    group->setExclusive(false);
    lowToHigh->setChecked(false);
    highToLow->setChecked(false);
    group->setExclusive(true);

    categories->setExclusive(false);
    furniture->setChecked(false);
    electronics->setChecked(false);
    clothes->setChecked(false);

    categories->setExclusive(true);
}
void MainWindow::populateInventory(Inventory &inv)
{
    ifstream file(R"(C:\Users\kalal\OneDrive\Documents\LoginPage\Inventory.txt)");
    string line;

    if (!file.is_open()) {
        cout << "Error opening draft3.txt" << endl;
        return;
    }

    while (getline(file, line)) {
        istringstream ss(line);
        string name, priceStr, category, details;
        double price;

        getline(ss, name, ',');
        getline(ss, priceStr, ',');
        getline(ss, category, ',');
        getline(ss, details, ',');
        price = stod(priceStr);

        if (category == "Electronics") {
            string company, type, specifications;
            getline(ss, company, ',');
            getline(ss, type, ',');
            getline(ss, specifications, ',');
            Electronics* e = new Electronics(name, price, category, details, company, type, specifications);
            inv.addProduct(e);
        }
        else if (category == "Clothes") {
            string size, material, type, brand;
            getline(ss, size, ',');
            getline(ss, material, ',');
            getline(ss, type, ',');
            getline(ss, brand, ',');
            Clothes* c = new Clothes(name, price, category, details, size, material, type, brand);
            inv.addProduct(c);
        }
        else if (category == "Furniture") {
            string woodType, type, specifications;
            getline(ss, woodType, ',');
            getline(ss, type, ',');
            getline(ss, specifications, ',');
            Furniture* f = new Furniture(name, price, category, details, woodType, type, specifications);
            inv.addProduct(f);
        }
    }

    file.close();
}
void MainWindow::productClick(string name)
{
    if (productinfo!=nullptr) {
        productinfo->close();
        productinfo = nullptr;
    }
    productinfo=new ProductInfo(inventory,cart,name,this);

    productinfo->setGeometry(QRect(50, 400+50, 400, 300));
    productinfo->show();

}
void MainWindow::filteringCategory(int state, string category, QWidget *container)
{

    vector<Product*> product;

    product=inventory.getAllProducts();
    for(QObject *child : container->children()) {
        QLabel *label = qobject_cast<QLabel*>(child);
        if(label && (label->objectName()=="keep")) continue;

        QWidget *widget = qobject_cast<QWidget*>(child);
        if(widget) widget->deleteLater();
    }
    int count=0;

    for(int i=0;i<product.size();i++)
    {
        if(product[i]->getCategory()== category)
        {
            count++;
        }
    }

    std::vector<QPushButton*> searchedItems(count);
    std::vector<Product*> products;
    count=0;
    for(int i=0;i<product.size();i++)
    {
        if(product[i]->getCategory() == category)
        {
            searchedItems[count] = new QPushButton(QString::number(count+1) + ". " + QString::fromStdString(product[i]->getName()), container);
            searchedItems[count]->setStyleSheet("color:white; font-size:14px; text-align: left; padding-left: 10px;");
            searchedItems[count]->setGeometry(30,50+(count*30),200,25);
            searchedItems[count]->show();
            QLabel *pricevalue = new QLabel("$ "+QString::number(product[i]->getPrice()),container);
            pricevalue->setGeometry(400,50+(count*30),50,25);
            pricevalue->setStyleSheet("border:none");
            pricevalue->show();
            products.push_back(product[i]);
            connect(searchedItems[count],&QPushButton::clicked,this,[=]{productClick(product[i]->getName());});
            count++;
        }
    }
    if(lowToHigh->isChecked())
    {
        for(QObject *child : container->children()) {
            QLabel *label = qobject_cast<QLabel*>(child);
            if(label && (label->objectName()=="keep")) continue;

            QWidget *widget = qobject_cast<QWidget*>(child);
            if(widget) widget->deleteLater();
        }
        filteringPrice(lowToHigh,container,products);
    }
    else if(highToLow->isChecked())
    {
        for(QObject *child : container->children()) {
            QLabel *label = qobject_cast<QLabel*>(child);
            if(label && (label->objectName()=="keep")) continue;

            QWidget *widget = qobject_cast<QWidget*>(child);
            if(widget) widget->deleteLater();
        }
        filteringPrice(highToLow,container,products);
    }
    search_bar->clear();
    clear->show();

}
