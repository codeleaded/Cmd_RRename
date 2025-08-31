#include "/home/codeleaded/System/Static/Library/GSprite.h"
#include "/home/codeleaded/System/Static/Library/Sprite.h"

#define SPRITE_PATH         "/home/codeleaded/Data/NN/Digits/"
#define SPRITE_TARGET       "/home/codeleaded/Data/NN/DigitsGray/"
#define SPRITE_TEST         "testing"
#define SPRITE_TRAINING     "training"
#define SPRITE_COUNT        300

Vector foundfiles;

void Filerename(char* path){
    Vector_Push(&foundfiles,(CStr[]){ CStr_Cpy(path) });
}

int main(){
    foundfiles = Vector_New(sizeof(CStr));
    /*
    for(int i = 0;i<10;i++){
        //SPRITE_TEST
        CStr rtraining = CStr_Format(SPRITE_PATH SPRITE_TRAINING "/%d",i);
        Files_Walk(rtraining,Filerename);
        CStr_Free(&rtraining);

        for(int j = foundfiles.size - 1;j>=0;j--){
            CStr path = *(CStr*)Vector_Get(&foundfiles,j);
            
            CStr abspath = Files_Path(path);
            CStr newname = CStr_Format("%s/D%d.png",abspath,j);
            printf("Remaned: %s to %s\n",path,newname);

            if (rename(path,newname) == 0) {
                printf("Filerename -> Datei erfolgreich umbenannt.\n");
            } else {
                printf("Filerename -> Fehler beim umbenennen der Datei.\n");
            }
        
            CStr_Free(&newname);
            CStr_Free(&abspath);
            CStr_Free(&path);
        }
        Vector_Clear(&foundfiles);
    }
    Vector_Free(&foundfiles);
    */
    
    for(int i = 0;i<10;i++){
        for(int j = 0;j<SPRITE_COUNT;j++){
            CStr ntraining_l = CStr_Format(SPRITE_PATH SPRITE_TRAINING "/%d/D%d.png",i,j);
            Sprite sp_training = Sprite_Load(ntraining_l);
            CStr_Free(&ntraining_l);

            CStr ntest_l = CStr_Format(SPRITE_PATH SPRITE_TEST "/%d/D%d.png",i,j);
            Sprite sp_test = Sprite_Load(ntest_l);
            CStr_Free(&ntest_l);

            GSprite g_training = GSprite_BySprite(sp_training.w,sp_training.h,sp_training.img);
            GSprite g_test = GSprite_BySprite(sp_test.w,sp_test.h,sp_test.img);

            CStr ntraining_s = CStr_Format(SPRITE_TARGET SPRITE_TRAINING "/%d/%d.sprg",i,j);
            GSprite_Save(&g_training,ntraining_s);
            CStr_Free(&ntraining_s);

            CStr ntest_s = CStr_Format(SPRITE_TARGET SPRITE_TEST "/%d/%d.sprg",i,j);
            GSprite_Save(&g_test,ntest_s);
            CStr_Free(&ntest_s);
            
            GSprite_Free(&g_test);
            GSprite_Free(&g_training);

            Sprite_Free(&sp_test);
            Sprite_Free(&sp_training);
        }
    }

    for(int j = foundfiles.size - 1;j>=0;j--){
        CStr* path = (CStr*)Vector_Get(&foundfiles,j);
        CStr_Free(path);
    }
    Vector_Free(&foundfiles);

    return 0;
}
