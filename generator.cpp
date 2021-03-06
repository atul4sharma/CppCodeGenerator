#include "generator.h"
#include <QDateTime>

int Generator::generateCode(char** argv){

    /***********************************************************************************/
    // To check whether user has input any argument or not
    /***********************************************************************************/
    QString classDetails;
    if(argv[1]){
        classDetails.append(argv[1]);
    }else {
        qDebug() << "No files are generated ";
        return -1;
    }
    /***********************************************************************************/

    /***********************************************************************************/
    // To check whether number of data members entered matches the number of types
    /***********************************************************************************/
    QStringList listDetails = classDetails.split(',');


    if( listDetails.size() % 2 == 0 || listDetails.size() == 0){
        qDebug() << "No files are generated !! Check number of data members.";
        return -1;
    }
    /***********************************************************************************/

    QString className = listDetails.at( 0 );
    className[0] = className[0].toUpper();

    QString fileName = className.toLower();

    int listCounter = 1;

    QString headerFileName = QString(fileName + ".h");
    QString sourceFileName = QString(fileName + ".cpp");

    /**
     * @brief dataTypes
     * List of data types of data members variables
     */
    QStringList dataTypes;

    /**
     * @brief dataMembers
     * List of data members variables corresponding to data type
     */
    QStringList dataMembers;

    for( ; listCounter < listDetails.size() ; listCounter+=2 ){

        QString memName('m'+listDetails.at(listCounter));
        memName[1] = memName[1].toUpper();

        dataMembers << memName;
        dataTypes << listDetails.at(listCounter+1);
    }

    generateHeaderFile(className, fileName, dataMembers, dataTypes, dataMembers.size());
    generateSourceFile(className, fileName, dataMembers, dataTypes, dataMembers.size());

}

/**
 * @brief Generator::generateHeaderFile
 * Generates and save header file
 */
void Generator::generateHeaderFile(const QString className,
                                   const QString fileName,
                                   const QStringList dataMembers,
                                   const QStringList dataTypes,
                                   int sizeOfDataMembers
                                   )
{
    QByteArray headerFileData;
    addTextStamp(headerFileData);
    headerFileData.append(QString("\n#ifndef "+className.toUpper()+"_H"));
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
        headerFileData.append(QString("\t\t" + dataTypes.at(i)+" get" + tempName + " () const;\n"));
    }

    headerFileData.append(QString("\n};\n\n"));
    headerFileData.append(QString("#endif // " + className.toUpper() + "_H\n"));

    QSaveFile headerFile(QString(fileName+".h"));
    headerFile.open(QIODevice::WriteOnly);
    headerFile.write(headerFileData);
    headerFile.commit();

}

/**
 * @brief Generator::generateSourceFile
 * Generate and save source file
 */
void Generator::generateSourceFile(const QString className,
                                   const QString fileName,
                                   const QStringList dataMembers,
                                   const QStringList dataTypes,
                                   int sizeOfDataMembers)
{

    QByteArray sourceFileData;

    addTextStamp(sourceFileData);
    sourceFileData.append("#include \"" + fileName + ".h\"\n\n");

    sourceFileData.append(className + "::" + className + "(){\n\n}\n" );

    //setter functions
    for( int i = 0 ; i < sizeOfDataMembers ; i++){

        QString tempName(dataMembers.at(i));
        tempName = tempName.remove(0,1);
        sourceFileData.append(QString("void "+ className +"::set" + tempName + "("
                                      + dataTypes.at(i)+ " val){\n"));
        sourceFileData.append(QString("\t" + dataMembers.at(i) + " = val ;\n"));

        sourceFileData.append(QString("}\n\n"));
    }

    //getter functions
    for( int i = 0 ; i < sizeOfDataMembers ; i++){

        QString tempName(dataMembers.at(i));
        tempName = tempName.remove(0,1);
        sourceFileData.append(QString( dataTypes.at(i) + " " +
                                      className + "::get" + tempName + " () const{\n"));
        sourceFileData.append(QString("\treturn this->" + dataMembers.at(i) + ";\n"));

        sourceFileData.append(QString("}\n\n"));
    }

    QSaveFile sourceFile(QString(fileName+".cpp"));
    sourceFile.open(QIODevice::WriteOnly);
    sourceFile.write(sourceFileData);
    sourceFile.commit();

}

/**
 * @brief Generator::addTextStamp
 * Just a text stamp
 */
void Generator::addTextStamp(QByteArray &data){
    data.append(QString("//This file is generated by CODE GEN Version "));
    data.append(QString::number(VERSION));
    data.append(QString(" on " +QDateTime::currentDateTime().toString() +"\n//Atul Sharma\n"));
}
