#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "zcj_const.h"
#include "zcj_type.h"
#include "zcj_util.h"

static char upper_digits[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static char lower_digits[]="0123456789abcdefghijklmnopqrstuvwxyz";

#define DIGITS upper_digits

/*
  功能：
  把字符串转化位整型数据
  参数：
  result：保存结果的整型数据指针
  str：待转化位整型数据的字符串
  返回值：
  转化成功返回true（str首尾含有空格外，其他位置均位数字）
  否则返回false
*/
int Str2Int(int *result,const u8 *str){
    int res=0;
    u8 *p=(u8 *)str;
    
    Trim(p,true,true);/*踢除前导和后导空格*/
    
    while(*p){
        if('0'<=*p && *p<='9'){
            res=res*10+(*p-'0');
            p++;
        }
        else
	    break;
    }	
    if(result!=NULL){
	*result=res;
    }
	
    return res;
}

/*
  功能：
  把整型数据转化为对应字符串
  参数：
  str：保存结果的字符串首地址
  value：待转换的整型数据
  返回值：
  转化成字符串的首地址
*/
u8* Int2Str(u8 *str,const int value){
    int v=value;
    u8 *p=str;

    while(v>0){
        (*p++)=DIGITS[v%10];
        v=v/10;
    }
    *p=0;

    StringReverse(str);

    return str;
    /* return null; */
}



/*
  功能：
  把8位二进制（u8）转换成两位十六进制
  参数：
  str：保存十六进制结果的首地址
  value：待转换的8位二进制
  返回值：
  两位十六进制的首地址
*/
u8* Char2Hexs(u8 *str,const u8 value){
    u8 tmp=0;

    tmp=(value>>4) & 0xF;
    *str=DIGITS[tmp];

    tmp=value & 0xF;
    *(str+1)=DIGITS[tmp];
    
    *(str+2)=0;

    return str;
}

/*
  功能：
  把两个十六进制转化成一个字符
  参数：
  value：两个十六进制对应的字符
  str：十六进制串
  返回值：
  由两个十六进制获得的字符
*/
u8 Hexs2Char(u8 *value,const u8 *str){

    assert(IsLegalForHex(*str));
    if('0'<=*str && *str<='9'){
        *value=(*str-'0')*16;
    }
    else if('A'<=*str && *str<='F'){
        *value=(*str-'A'+10)*16;
    }else{
        *value=(*str-'a'+10)*16;
    }

    assert(IsLegalForHex(*(str+1)));
    if('0'<=*(str+1) && *(str+1)<='9'){
        *value+=(*(str+1)-'0');
    }
    else if('A'<=*(str+1) && *(str+1)<='F'){
        *value+=(*(str+1)-'A'+10);
    }
    else{
        *value+=(*(str+1)-'a'+10);
    }
}

/*
  功能：
  将浮点数转化位字符串。
  但是由于浮点数的精度问题，有时，输出的字符串并不完全跟你所期望的一样，而是字符串对应的浮点数与实际数值近似相等。
  参数：
  str:字符串保存地址
  float：待转化的浮点数
  count:保留小数点后的位数
  返回值：
  字符串的首地址
*/
u8 *Float2Str(u8 *str,const float f,const int count){
    float tf=f;
    int tc=count;
    u8 *p=0;
 
    while(tc){
        tf=tf*10;
        --tc;
    }
    Int2Str(str,(const int)tf);
    
    p=str+strlen(str);//指向字符串结束标志'\0'
    tc=count+1;//count个数字和字符串尾部的0
    while(tc){
        *(p+1)=*p;
        p--;
        tc--;
    }
    *(p+1)='.';

    return str;
}


float Str2Float(float *f,const u8 *str){
    float res=0;
    float base=1;
    float fbase=0.1;
    bool point=false;
    int index;

    for(index=0;index<strlen(str);index++){
        u8 c=*(str+index);
        if(IsNum(c) || c=='.'){
            if(point){/*小数部分*/
                if(IsNum(c)){
                    res+=base*(c-'0');
                    base*=fbase;
                }
                else{
                    break;/*遇到第二个'.'，是非法字符*/
                }
            }
            else{/*整数部分*/
                if(IsNum(c)){
                    res=res*10+(c-'0');
                }
                else{
                    point=true;/*遇到第一个'.'，是合法的小数点*/
                    base=fbase;
                }
            }
        }
        else{
            break;/*遇到不合法的字符，停止处理*/
        }
    }

    if(f!=NULL){
        *f=res;
    }
    return res;
}

/*
  功能：
  把十六进制串转化成对应的字符串（两个十六进制表示一个字符）
  参数：
  des:转化后得到的字符串
  src:十六进制串
  count:十六进制转化的长度
  返回值：
  转化后得到的字符串
*/
u8 *Hexs2Str(u8 *des,const u8 *src,int count){
    int index;

    if(count<0){
        count=0;
    }
    else if(count>strlen(src)){
        count=strlen(src);
    }

    for(index=0;index<count/2;index++){
        Hexs2Char(des+index,src+2*index);
    }
    *(des+count/2)=0;/*字符串结束标志*/

    return des;
}

/*
  功能：
  把字符串转化成对应的十六进制字符串
  参数：
  des:转化后得到的十六进制串
  src:待转化处理的字符串
  count:处理字符串的长度
  返回值：
  转化后得到的十六进制串的首地址
*/
u8 *Str2Hexs(u8 *des,const u8 *src,int count){  
    int index;

    if(count<0){
        count=0;
    }
    else if(count>strlen(src)){
        count=strlen(src);
    }

    for(index=0;index<count;index++){
        Char2Hexs(des+2*index,*(src+index));
    }
    *(des+2*count)=0;/*字符串结束标志*/
    
    return des; 
}

/*
  功能：
  判断字符是否位空字符
  参数：
  c：待判断的字符
  返回值：
  如果是空字符，返回true；
  否则返回false。
*/
bool IsSpace(u8 c){
    u8 space[]={' ','\t'};
    int index;

    for(index=0;index<strlen(space);index++){
        if(c==space[index])
            return true;
    }
    return false;
}

bool IsNum(u8 c){
    return '0'<=c && c<='9';
}

bool IsAlpha(u8 c){
    return IsUpper(c) || IsLower(c);
}

bool IsUpper(u8 c){
    return 'A'<=c && c<='Z';
}

bool IsLower(u8 c){
    return 'a'<=c && c<='z';
}

bool IsLegalForHex(u8 c){
    return IsNum(c) || ('A'<=c && c<='F') || ('a'<=c && c<='f');
}

/*
  功能：
  根据参数值决定是否踢除字符串首尾的空字符
  参数：
  str：待处理的字符串
  begin：是否踢除首部的空字符
  end：是否踢除尾部的空字符
  返回值：
  处理完后字符串的首地址
*/
u8 *Trim(u8 *str,bool begin,bool end){
    u8 *p=0;
    u8 *q=0;
    u8 *lower=str;
    u8 *upper=str+strlen(str)-1;
    
    while(IsSpace(*lower)){
        lower++;
    }
    while(IsSpace(*upper))
        upper--;
    *(upper+1)=0;
    
    p=str;
    q=lower;
    while(q<=upper){
        (*p++)=(*q++);
        
    }
    *p=0;
    return str;
}

/*
  功能：
  把字符串初始化为指定字符
  参数：
  str：待初始化的字符串
  c：指定的字符
  length：初始化字符串的长度
  返回值：
  初始化的字符串的首地址
*/
u8 *StringInit(u8 *str,u8 c,int length){
    int index;
    
    for(index=0;index<length;index++){
        *(str+index)=c;
    }
    *(str+index)=0;/*字符串结束标志*/
    
    return str;
}

/*
  功能：
  在字符串指定位置插入指定个数的指定字符，之前的字符顺后移
  参数：
  str：待插入的字符串
  ch：指定插入的字符
  begin：插入的起始下标
  length：插入指定字符的个数
  返回值：
  处理完后字符串的首地址
*/
u8 *InsertNChar(u8 *str,u8 ch,int begin,int length){
    int index;
    u8 *p=0;
    
    if(begin<0){
        begin=0;
    }
    else if(begin>strlen(str)){
        begin=strlen(str);
    }

    p=str+strlen(str);//指向字符串的结束标志(\0)
    for(index=strlen(str)+length;index>=begin+length;index--){
        *(str+index)=*(str+index-length);
    }

    for(index=begin+length-1;index>=begin;index--){
        *(str+index)=ch;
    }
    return str;
}

/*
  功能：
  从字符串的指定位置开始复制指定长度的子串
  参数：
  des：子串的首地址
  src：原始串的首地址
  begin：子串在原始串中的起始下标
  count：子串的长度
  返回值：
  子串的首地址
*/
u8 *StringNCopy(u8 *des,const u8 *src,int begin,int count){
    int index;
    u8 *p=des;

    /*处理不合法的begin,count,使之合法*/
    if(begin<0 || begin >=strlen(src)){
        begin=0;
    }
    if(count<0 )
    {
        count=0;
    }
    else if(begin+count>strlen(src)){
        count=strlen(src)-begin;
    }

    /*字符串复制，可以成功处理des和src有重叠部分的情况*/
    if(des<src+begin){
        for(index=begin;index<begin+count;index++){
            *(des+index-begin)=*(src+index);
        }
    }
    else if(des>src+begin){
        for(index=begin+count-1;index>=begin;index--){
            *(des+index-begin)=*(src+index);
        }
    }
    
    *(des+count)=0;/*字符串结束标志*/
    return des;
}

/*
  功能：
  字符串反转
  参数：
  str：待处理（反转）的字符串
  返回值：
  处理结果的字符串的首地址
*/
u8* StringReverse(u8 *str){
    u8* lower=str;
    u8* upper=str+strlen(str)-1;
    u8 tmp=0;
    
    while(lower<upper){
        tmp=*lower;
        *lower=*upper;
        *upper=tmp;

        ++lower;
        --upper;
    }
    return str;
}

/*
  功能：
  将c（0<=c<100）表示成对应的字符串，如c=13，buf=“13”
  参数：
  返回值：
*/
char* Char2Ints(char *des,char c){
    des[0]=c/10+'0';
    des[1]=c%10+'0';

    return des;
}

/*
  功能：
  将整数字符串"d1d2",转化为对应的字符(d1-'0')*10+(d0-'0')
  参数：
  返回值：
*/
//src="23" return 23;
char Ints2Char(const char *src){
    return (src[0]-'0')*10+(src[1]-'0');
}

/*
  功能：
  扩展浮点数字符串转化为对应的满足要求格式的浮点字符串
  参数：
  dest:目的浮点字符串
  src:源浮点字符串
  int_len:目标整数部分数字位数，不够补'0'
  frac_len:目标小数部分数字位数，不够补'0'
  返回值：
*/
char* ExtendFloatStr(char *dest,const char *src,int int_len,int frac_len){

    int index;
    char *dot=strchr(src,'.');

    const char *p;

    memset(dest,'0',int_len+1+frac_len);
    dest[int_len]='.';
    dest[int_len+1+frac_len]=0;

    if(dot==NULL){
	index=int_len-1;
	for(p=src+strlen(src)-1;p>=src && index>=0;p--){
	    dest[index--]=*p;
	}
    }
    else{
	index=int_len-1;
	for(p=dot-1;p>=src && index>=0;p--){
	    dest[index--]=*p;
	}
	index=int_len+1;
	for(p=dot+1;p<src+strlen(src) && index<int_len+1+frac_len;p++){
	    dest[index++]=*p;
	}
    }
    
    return dest;
}

/*
  功能：
  删除整数字符串的前导'0'
  参数：
  dest:整数字符串
  返回值：
*/
void TrimInts(char *dest){
    int index,st;

    for(index=0;index<strlen(dest)-1;index++){
	if(dest[index]!='0')
	{
	    break;
	}
    }

    int in=0;
    for(;index<strlen(dest);index++){
	dest[in++]=dest[index];
    }
    dest[in]=0;
}

/*
  功能：删除浮点数整数部分前导'0'和小数部分后导'0'
  参数：
  dest:待处理浮点数字符串
  返回值：
*/
void TrimFloat(char *dest){
    char *dot;
    int index,st,end;

    if(strchr(dest,'.')==NULL){
	trimInt(dest);
    }else{
	st=0;
	for(index=0;index<strlen(dest);index++){
	    if(dest[index]!='0' || dest[index+1]=='.'){
		st=index;
		break;
	    }
	}

	end=strlen(dest)-1;
	for(index=strlen(dest)-1;index>=0;index--){
	    if(dest[index]!='0'){
		if(dest[index]=='.'){
		    end=index-1;
		}else{
		    end=index;
		}
		break;
	    }
	}
	int in=0;
	for(index=st;index<=end;index++){
	    dest[in++]=dest[index];
	}
	dest[in]=0;
    }
}

/*
  功能：延时sec秒，由于是分时系统，所以实际是至少延时sec秒
  参数：
  sec:指定延时秒数
  返回值：
*/
void Delay(int sec){
    time_t start,current;

    time(&start);
    do{
	time(&current);
    }while(current-start<sec);
}
