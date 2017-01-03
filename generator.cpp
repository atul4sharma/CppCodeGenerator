#include "generator.h"

int Generator::generateCode(char** argv){

    QString classDetails(argv[1]);

    QStringList listDetails = classDetails.split(',');


    if( listDetails.size() % 2 == 0){
        return -1;
    }

    QString className = listDetails.at( 0 );
    className[0] = className[0].toUpper();

    QString fileName = className;
    fileName[0] = fileName[0].toLower();

    int listCounter = 1;

    QString headerFileName = QString(className + ".h");
    QString sourceFileName = QString(className + ".cpp");

    QStringList dataTypes;
    QStringList dataMembers;

    for( ; listCounter < listDetails.size() ; listCounter+=2 ){

        QString memName('m'+listDetails.at(listCounter));
        memName[1] = memName[1].toUpper();

        dataMembers << memName;
        dataTypes << listDetails.at(listCounter+1);
    }

    generateHeaderFile(className, fileName, dataMembers, dataTypes, dataMembers.size());
    //generateSourceFile(className, dataMembers, dataTypes, dataMembers.size());

}

void Generator::generateHeaderFile(const QString className, const QString fileName,
                                   const QStringList dataMembers,
                                   const QStringList dataTypes,
                                   int sizeOfDataMembers
                                   )
{
    QByteArray headerFileData;
    headerFileData.append(QString("#ifndef "+className.toUpper()+"_H"));
    headerFileData.append('\n');
    headerFileData.append(QString("#define "+className.toUpper()+"_H"));
    headerFileData.append('\n');
    headerFileData.append('\n');

    headerFileData.append(QString("class " + className + " {\n" ));
    headerFileData.append(QString("\n\tprivate:\n"));



    for( int i = 0 ; i < sizeOfDataMembers ; i++){

        headerFileData.append(QString("\t\t" + dataTypes.at(i) + " " +
                                      dataMembers.at(i) + ";\n"));
    }


    headerFileData.append(QString("\n\tpublic:\n"));
    headerFileData.append(QString("\t\texplicit "+ className + "();\n\n"));

    //setter functions
    for( int i = 0 ; i < sizeOfDataMembers ; i++){

        QString tempName(dataMembers.at(i));
        tempName = tempName.remove(0,1);
        headerFileData.append(QString("\t\tvoid set" + tempName + "("
                                      + dataTypes.at(i)+ " val);\n"));
    }

    headerFileData.append('\n');
    //getter functions
    for( int i = 0 ; i < sizeOfDataMembers ; i++){

        QString tempName(dataMembers.at(i));
        tempName = tempName.remove(0,1);
        headerFileData.append(QString("\t\tconst "+dataTypes.at(i)+" get" + tempName + "();\n"));
    }

    headerFileData.append(QString("\n};\n\n"));
    headerFileData.append(QString("#endif " + className.toUpper() + "_H\n"));

    QSaveFile headerFile(QString(fileName+".h"));
    headerFile.open(QIODevice::WriteOnly);
    headerFile.write(headerFileData);
    headerFile.commit();

}

