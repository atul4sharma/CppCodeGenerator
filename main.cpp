// Input - classname,{datamember,datatype}

#include <QCoreApplication>

#include "generator.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc,argv);
    qDebug() << "CODE GEN VERSION : " << VERSION ;

    int returnCode = Generator::generateCode(argv);
    app.exit(returnCode);
}
