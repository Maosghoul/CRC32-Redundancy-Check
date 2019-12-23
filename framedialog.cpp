#include "framedialog.h"
#include "ui_framedialog.h"
#include <bits/stdc++.h>
#include <QDebug>
using namespace std;

string s;
string input;
string crc32 = "100000100110000010001110110110111"; //CRC32 的标准二进制
string dePix="8000ff602cdc"; // 预制好的，可以更改为输出
string souPix="8000fe853a5f";  //预制好的，可以更改为输出
string lenPix="0040";    //长度 the length

char ff(int x){
    if(x>=10) return x-10+'a';
    else return x+'0';
}

string init()
{
    string res="";
    for(int i=0;i<(int)input.size();i++){
        bitset<8> st(input[i]-'\0');
        string t = st.to_string();
        int t1 = (t[0]-'0')*8+(t[1]-'0')*4+(t[2]-'0')*2+t[3]-'0';
        int t2 = (t[4]-'0')*8+(t[5]-'0')*4+(t[6]-'0')*2+t[7]-'0';
        string tmp="";
        tmp+=ff(t1);
        tmp+=ff(t2);
        res+=tmp;
    }
    return res;
}




FrameDialog::FrameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrameDialog)
{
    ui->setupUi(this);
}

FrameDialog::~FrameDialog()
{
    delete ui;
}

string solve(){
    string dataPix = init();
    if(input.size()<46){
        int cnt = 46-input.size();
        while(cnt--){
            dataPix+="00";
        }
    }
    s=dePix+souPix+lenPix+dataPix;

    int Tcnt = 4;
    while(Tcnt--) s+="00";

    string ans ="";
    string t;
    for(int i=0;i<(int)s.size();i++){
        if(s[i]>='a'&&s[i]<='f'){
            bitset<4> st(s[i]-'a'+10);
            t = st.to_string();
        }
        else if(s[i]>='0'&&s[i]<='9'){
            bitset<4> st(s[i]-'0');
            t = st.to_string();
        }
        ans+=t;
    }
    int len = crc32.size();
    string x="";
    for(int i=0;i<len;i++){
        x+=ans[i];
    }
    string  tmp;
    for(int i=len;i<(int)ans.size();i++){
        tmp="";
        if(x[0]=='1'){
            for(int j=1;j<len;j++)
            {
                if(x[j]==crc32[j]){
                    tmp+='0';
                }
                else{
                    tmp+='1';
                }
            }
        }
        else{
            for(int j=1;j<len;j++){
                tmp+=x[j];
            }
        }
        tmp+=ans[i];
        x=tmp;
    }
    tmp="";
    for(int j=1;j<len;j++)
    {
        if(x[j]==crc32[j]){
            tmp+='0';
        }
        else{
            tmp+='1';
        }
    }

    string myFrameAns="";
    for(int i=0;i<(int)tmp.size();i+=4){
        int  tt= (tmp[i]-'0')*8+(tmp[i+1]-'0')*4+(tmp[i+2]-'0')*2+tmp[i+3]-'0';
        if(tt>=10){
            char sp = tt-10+'A';
            myFrameAns+=sp;

        }
        else{
            char sp = tt+'0';
            myFrameAns+=sp;

        }
    }
    return myFrameAns;

}


void FrameDialog::on_pushButton_clicked()
{
    QString a = ui->lineEdit->text();
    input = a.toStdString();

    QString bb = QString::fromStdString(solve());
    ui->lineEdit_2->setText(bb);
}
