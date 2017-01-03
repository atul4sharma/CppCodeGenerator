#ifndef GENERATOR_H
#define GENERATOR_H

#include <QDebug>
#include <QFile>
#include <QSaveFile>

class Generator
{
public:
    static int generateCode(char**);
    static void generateHeaderFile(const QString className,
                            const QString fileName,
                            const QStringList dataMembers,
                            const QStringList dataTypes,
                            int sizeOfDataMembers);

    static void generateSourceFile(const QString className,
                            const QString fileName,
                            const QStringList dataMembers,
                            const QStringList dataTypes,
                            int sizeOfDataMembers);
};

#endif // GENARATOR_H
