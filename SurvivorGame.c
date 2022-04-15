#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

FILE *dosya;
    struct
    {
      int EngelSayisi;
      int BitisMetresi;
    }Parkur;

 int HP,*Engelcikismetresi,i,j,gecici,Kucuksayi,sayac=0;
 HP=100;

int main()
{
    Engeller();
    EngelKarsilasma();

    return 0;
}

void Engeller()
{
    srand(time(0));
    Parkur.EngelSayisi=rand()%4+2;
    Parkur.BitisMetresi=rand()%51+50;
    Engelcikismetresi=(int *)malloc(sizeof(int)*Parkur.EngelSayisi);
    if(Engelcikismetresi==NULL)
    {
        printf("Yetersiz Bellek!");
    }

    for(i=0;i<Parkur.EngelSayisi;i++)
    {
        Engelcikismetresi[i]=rand()%(Parkur.BitisMetresi-4)+5;
    }

    for(i=0;i<Parkur.EngelSayisi;i++)
    {
        for(j=0;j<Parkur.EngelSayisi-1;j++)
        {
            if(Engelcikismetresi[j]>Engelcikismetresi[j+1])
            {
                gecici=Engelcikismetresi[j];
                Engelcikismetresi[j]=Engelcikismetresi[j+1];
                Engelcikismetresi[j+1]=gecici;
            }
        }
    }
}

void EngelKarsilasma()
{
   dosya=fopen("log.txt","w+");
   if(dosya==NULL)
   {
       printf("log.txt dosyasi acilamadi!\n");
       exit(1);
   }
   fprintf(dosya,"Yarisma basladi!\n");

   for(i=0;i<Parkur.EngelSayisi;i++)
   {
       if(Engelcikismetresi[i]<HP)
       {
           Kucuksayi=Engelcikismetresi[i];
       }
       else
       {
           Kucuksayi=HP;
       }

       for(j=2;j<=Kucuksayi;j++)
       {
           if(Engelcikismetresi[i]%j==0 && HP%j)
           {
               sayac=1;
           }
       }
           if(sayac==0)
           {
               if(HP<=0)
                break;
               fprintf(dosya,"Yarismaci HP=%d\n",HP);
               fprintf(dosya,"Yarismaci %d. metreye kadar bir engelle karsilasmadi.\n",Engelcikismetresi[i]);
               fprintf(dosya,"%d. metrede bir engel var.%d ve %d aralarinda asaldir.\n",Engelcikismetresi[i],HP,Engelcikismetresi[i]);
           }
           else
           {

               fprintf(dosya,"Yarismaci HP=%d\n",HP);
               fprintf(dosya,"Yarismaci %d. metreye kadar bir engelle karsilasmadi.\n",Engelcikismetresi[i]);
               fprintf(dosya,"%d. metrede bir engel var.%d ve %d aralarinda asal degildir.\n",Engelcikismetresi[i],HP,Engelcikismetresi[i]);
               HP-=Engelcikismetresi[i];
               if(HP<=0)
                break;
           }
   }
   fprintf(dosya,"Yarismaci HP=%d\n",HP);
   if(HP<=0)
   {
       fprintf(dosya,"UZGUNUM!! Yarismayi tamamlayamadin.\n");
   }
   else
   {
       fprintf(dosya,"TEBRIKLER!! %d HP ile yarismayi tamamladiniz.\n",HP);
   }

   fclose(dosya);
}
