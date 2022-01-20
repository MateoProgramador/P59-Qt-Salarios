#include "salarios.h"
#include "ui_salarios.h"

Salarios::Salarios(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Salarios)
{
    ui->setupUi(this);
    m_controlador = new Controlador();
    m_salarioBruto = 0;
    m_descuento = 0;
    m_total = 0;
}

Salarios::~Salarios()
{
    delete ui;
}


void Salarios::on_cmdCalcular_clicked()
{
    calcular();
}

void Salarios::limpiar()
{
    ui->inNombre->setText("");
    ui->inHoras->setValue(0);
    ui->inMatutino->setChecked(true);
    ui->inNombre->setFocus();

}

void Salarios::guardar()
{
    // Abrir cuadro de diálogo para seleccionar ubicación y nombre del archivo.
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         "Guardar archivo",
                                                         QDir::home().absolutePath(),
                                                         "Archivos de salarios (*.slr)");

    // Crear un objeto QFile
    QFile archivo(nombreArchivo);
    // Abrirlo para escritura
    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
        // Crear un 'stream' de texto
        QTextStream salida(&archivo);
        // Enviar los datos del resultado a la salida
        salida << ui->outResultado->toPlainText();
        salida.operator<<("\n-----------------------------");
        salida.operator<<("\n" + QString::number(m_salarioBruto,'f',2) + "\n" + QString::number(m_descuento,'f',2) + "\n"
+ QString::number(m_total,'f',2));
        // Mostrar 5 segundo que todo fue bien
        ui->statusbar->showMessage("Datos almacenados en " + nombreArchivo, 5000);
    }else {
        // Mensaje de error si no se puede abrir el archivo
        QMessageBox::warning(this,
                             "Guardar datos",
                             "No se pudo guardar el archivo");
    }
    // Cerrar el archivo
    archivo.close();

}

void Salarios::abrir()
{
    // Abrir cuadro de diálogo para seleccionar ubicación y nombre del archivo.
    QString nombreArchivo = QFileDialog::getOpenFileName(this,
                                                         "Abrir archivo",
                                                         QDir::home().absolutePath(),
                                                         "Archivos de salarios (*.slr)");

    // Crear un objeto QFile
    QFile archivo(nombreArchivo);


    // Abrirlo para lectura
    if(archivo.open(QFile::ReadOnly)){
        // Crear un 'stream' de texto
        QTextStream entrada(&archivo);
        // Leer todo el contenido del archivo
        QString datos = "", almacenarLinea = "";
        while(entrada.atEnd()==false && almacenarLinea != "-----------------------------" ){
            almacenarLinea = entrada.readLine();
            datos += almacenarLinea + "\n";
        }
        ui->outBruto->setText(entrada.readLine());
        m_salarioBruto = ui->outBruto->text().toDouble();
        ui->outDescuento->setText(entrada.readLine());
        m_descuento = ui->outDescuento->text().toDouble();
        ui->outTotal->setText(entrada.readLine());
        m_total = ui->outTotal->text().toDouble();

        // Cargar el contenido al área de texto
        ui->outResultado->clear();
        ui->outResultado->setPlainText(datos);
        // Mostrar 5 segundo que todo fue bien
        ui->statusbar->showMessage("Datos leidos desde " + nombreArchivo, 5000);
    }else {
        // Mensaje de error si no se puede abrir el archivo
        QMessageBox::warning(this,
                             "Abrir datos",
                             "No se pudo abrir el archivo");
    }
    // Cerrar el archivo
    archivo.close();
}


void Salarios::on_actionCalcular_triggered()
{
    calcular();

    qDebug()<<m_salarioBruto;

}

void Salarios::calcular()
{
    // Obteber datos de la GUI
    QString nombre = ui->inNombre->text();
    int horas = ui->inHoras->value();
    TipoJornada jornada;
    if (ui->inMatutino->isChecked()){
        jornada = TipoJornada::Matutina;
    } else if (ui->inVespertina->isChecked()){
        jornada = TipoJornada::Vespertina;
    } else {
        jornada = TipoJornada::Nocturna;
    }

    // Validar datos correctos
    if (nombre == "" || horas == 0){
        /*
        QMessageBox msgBox;
        msgBox.setText("El nombre o el número de horas está vacío");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
        */
        QMessageBox::warning(this,"Advertencia","El nombre o el número de horas está vacío");
        return;
    }

    // Agregar obrero al controlador
    m_controlador->agregarObrero(nombre, horas, jornada);
    // Calcular
    if (m_controlador->calcularSalario()){
        // muestra los resultados de los calculos del obrero
        ui->outResultado->appendPlainText(m_controlador->obrero()->toString());
        // Mostrar mensaje por 5 segundos en la barra de estado
        ui->statusbar->showMessage("calculos procesados para " + nombre, 5000);
        m_salarioBruto += m_controlador->salBruto;
        m_descuento += m_controlador->descuentoSalario;
        m_total += m_salarioBruto - m_descuento;
        ui->outBruto->setText(QString::number(m_salarioBruto,'f',2));
        ui->outDescuento->setText(QString::number(m_descuento,'f',2));
        ui->outTotal->setText(QString::number(m_total,'f',2));

        // limpiar la interfaz
        limpiar();
    }else {
        QMessageBox::critical(
                    this,
                    "Error",
                    "Error al calcular el salario.");
    }
}


void Salarios::on_actionGuardar_triggered()
{
    guardar();

}


void Salarios::on_actionNuevo_triggered()
{
    limpiar();
    ui->outResultado->clear();
    m_salarioBruto = 0;
    m_descuento = 0;
    m_total = 0;
    ui->outBruto->setText("0.00");
    ui->outDescuento->setText("0.00");
    ui->outTotal->setText("0.00");

}


void Salarios::on_actionAbrir_triggered()
{
    abrir();
}

void Salarios::on_actionAcerca_de_salarios_triggered()
{
    //Crear un objeto de la ventana que queremos invocar
    acerca *dialogo = new acerca(this);
    //Enviar parametro a la ventana
    dialogo->setVersion(VERSION);
    //Mostrar la ventana de dialogo
    dialogo->exec();
    //Obtener datos del dialogo
    //dialogo->valor();

}

