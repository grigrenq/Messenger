#include "login_window.h"
#include "Avatar.cpp"
#include <iostream>


void login_window::create_layout(){
    mainLayout = new QGridLayout();
    leftSide   = new QVBoxLayout();
    rightSide  = new QVBoxLayout();
    messageBox = new QVBoxLayout();
    writeBox   = new QHBoxLayout();

    leftLabel = new QLabel(this);
    messageLabel = new QLabel(this);

    leftLabel->setMinimumWidth(200);
    leftLabel->setMaximumWidth(50);
    messageLabel->setMinimumHeight(600);

    QTextEdit *txt=new QTextEdit(this);

    writeBox->addWidget(txt);



    Avatar *a=new Avatar();
    Avatar *b=new Avatar();
    Avatar *c=new Avatar();
    Avatar *d=new Avatar();
    Avatar *l=new Avatar();
    Avatar *k=new Avatar();
    Avatar *j=new Avatar();
    Avatar *h=new Avatar();

//   a->setReadOnly(true); 
//   b->setReadOnly(true); 
//   c->setReadOnly(true); 
//   d->setReadOnly(true); 
//   l->setReadOnly(true); 
//   k->setReadOnly(true); 
//   j->setReadOnly(true); 
//   h->setReadOnly(true); 

a->setText("asdaasdasdas");
b->setText("asdaasdasdas");
c->setText("asdaasdasdas");
d->setText("asdaasdasdas");
l->setText("asdaasdasdas");
k->setText("asdaasdasdas");
j->setText("asdaasdasdas");
h->setText("asdaasdasdas");




    leftSide->setSizeConstraint(QLayout::SetMaximumSize);

    leftSide->addWidget(a);
    leftSide->addWidget(b);
    leftSide->addWidget(c);
    leftSide->addWidget(d);
    leftSide->addWidget(l);
    leftSide->addWidget(k);
    leftSide->addWidget(j);
    leftSide->addWidget(h);
    leftSide->addWidget(leftLabel);

  // QLabel *q=new QLabel("aaaaa",this);
  // QLabel *w=new QLabel("aiaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbb",this);
  // QLabel *e=new QLabel("aaaaa",this);
  // QLabel *r=new QLabel("aaaaa",this);
  // QLabel *p=new QLabel("aaaaa",this);
  // QLabel *o=new QLabel("aiaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbb",this);
  // QLabel *i=new QLabel("aaaaa",this);
  // QLabel *u=new QLabel("aaaaa",this);


    QLineEdit *messageText=new QLineEdit(this);

    messageText->setReadOnly(true);
    //QScrollBar *messageScrollBar = messageText ->verticalScrollBar();

    //messageScrollBar->setValue(messageScrollBar->maximum());

   
for (int i=0;i<20;++i){



    messageText->setText(messageText->text()+"bxkaaaaaaaa\n" + "\n\n");
    messageText->setText(messageText->text()+"bxkaaaaaaaa\n" + "\n\n");
    messageText->setText(messageText->text()+"bxkaaaaaaaa\n" + "\n\n");
    messageText->setText(messageText->text()+"bxkaaaaaaaa\n" + "\n\n");
}
    



  // messageLabel->addWidget(q);
  // messageLabel->addWidget(w);
  // messageLabel->addWidget(e);
  // messageLabel->addWidget(r);
  // messageLabel->addWidget(p);
  // messageLabel->addWidget(o);
  // messageLabel->addWidget(i);
  // messageLabel->addWidget(u);
   

    messageBox->addWidget(messageText);

    messageBox->addWidget(messageLabel);
     


    rightSide->addLayout(messageBox);
    rightSide->addLayout(writeBox);



    mainLayout->addLayout(leftSide,0,0);
    mainLayout->addLayout(rightSide,0,1);



    setLayout(mainLayout);
}
