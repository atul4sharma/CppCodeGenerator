#include <QCoreApplication>


#include "generator.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc,argv);
    int returnCode = Generator::generateCode(argv);
    app.exit(returnCode);
}
