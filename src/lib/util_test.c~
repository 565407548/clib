
/*测试脚手架*/
void Str2Int_test();
void Int2Str_test();
void Char2Hexs_test();
void Hexs2Char_test();
void Float2Str_test();
void Str2Float_test();
void Hexs2Str_test();
void Str2Hexs_test();

void Str2Int_Test(){
    int result;
    u8 str1[]="123.4d";
    u8 str2[]=" 1251 ";
    u8 str3[]="123c";
    
    	Str2Int(&result,str1);
        printf("str:\"%s\" int:%d\n",str1,result);
    	Str2Int(&result,str2);
        printf("str:\"%s\" int:%d\n",str2,result);
	Str2Int(&result,str3);
        printf("str:\"%s\" int:%d\n",str3,result);
}


void Int2Str_Test(){
    u8 str[10];
    int v;

    v=1234;
    Int2Str(str,v);
    printf("int:%d str:%s\n",v,str);

    v=123;
    Int2Str(str,v);
    printf("int:%d str:%s\n",v,str);

    v=54215198;
    Int2Str(str,v);
    printf("int:%d str:%s\n",v,str);
}

void Char2Hexs_Test(){
    u8 c;
    u8 str[5];

    c=6;
    Char2Hexs(str,c);
    printf("char:%c Hex:\"%s\"\n",c,str);

    c='0';
    Char2Hexs(str,c);
    printf("char:%c Hex:\"%s\"\n",c,str);

    c='A';
    Char2Hexs(str,c);
    printf("char:%c Hex:\"%s\"\n",c,str);
}



void Hexs2Char_Test(){
    u8 c;
    u8 str[5];

    strcpy(str,"41");
    Hexs2Char(&c,str);
    printf("str:\"%s\" char:%c\n",str,c);

    strcpy(str,"31");
    Hexs2Char(&c,str);
    printf("str:\"%s\" char:%c\n",str,c);

    strcpy(str,"gb");
    Hexs2Char(&c,str);
    printf("str:\"%s\" char:%c\n",str,c);
    
}


void Float2Str_Test(){
    float f;
    int c;
    u8 str[20];

    f=10.2315;
    c=2;
    Float2Str(str,f,c);
    printf("float:%f str:%s\n",f,str);

    f=10.2315;
    c=2;
    Float2Str(str,f,c);
    printf("float:%f str:%s\n",f,str);

    f=010.2315;
    c=4;
    Float2Str(str,f,c);
    printf("float:%f str:%s\n",f,str);
       
    f=10.23;
    c=4;
    Float2Str(str,f,c);
    printf("float:%f str:%s\n",f,str); 
}



void Hexs2Str_test(){
    u8 des[10];
    u8 src[2*10];

    strcpy(src,"31324152");
    Hexs2Str(des,src,strlen(src));
    printf("hexs:%s str:%s\n",src,des);

    strcpy(src,"3");
    Hexs2Str(des,src,strlen(src));
    printf("hexs:%s str:%s\n",src,des);

    strcpy(src,"gboiag");
    Hexs2Str(des,src,strlen(src));
    printf("hexs:%s str:%s\n",src,des);
}

void Str2Hexs_test(){
    u8 des[2*10];
    u8 src[10];

    strcpy(src,"123abc");
    Str2Hexs(des,src,strlen(src));
    printf("str:%s hexs:%s\n",src,des);

    strcpy(src,"aega2a");
    Str2Hexs(des,src,strlen(src));
    printf("str:%s hexs:%s\n",src,des);

    strcpy(src,"a");
    Str2Hexs(des,src,strlen(src));
    printf("str:%s hexs:%s\n",src,des);
}


void Trim_test(){
    u8 str[10];

    strcpy(str," 1dagi\t  ");
    Trim(str,true,true);
    printf("\"%s\"\n",str);
}


void InsertNChar_test(){
    u8 str[20]="01234";
    
    InsertNChar(str,'a',10,3);
    printf("%s\n",str);

    InsertNChar(str,'b',3,5);
    printf("%s\n",str);

    InsertNChar(str,'c',-1,2);
    printf("%s\n",str);
}


void StringNCopy_test(){
    u8 src[]="0123456789abc";
    u8 des[20];
    
    StringNCopy(des,src,3,3);
    printf("%s\n",des);

    StringNCopy(des,src,10,5);
    printf("%s\n",des);

    StringNCopy(src+5,src,3,3);
    printf("%s\n",src+5,des);

    StringNCopy(src+1,src,5,4);
    printf("%s\n",src+1);
}
