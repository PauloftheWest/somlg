#ifndef SOMLG_DIALOG_H
#define SOMLG_DIALOG_H

typedef struct _somlg_dialog {
    char *mMessage;
    char **mOptions;
    unsigned int mNumOptions;
    unsigned int mDecoration;
} somlg_dialog;

somlg_dialog* parseDialog(const char *str);
void freeDialog(somlg_dialog *dialog);
char *getMessage(const somlg_dialog *dialog);
unsigned int getNumOptions(const somlg_dialog *dialog);
char *getOption(const somlg_dialog *dialog, const int index);
int getDecorationId(const somlg_dialog *dialog);

#endif
