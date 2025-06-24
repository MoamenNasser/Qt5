#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTextEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDateEdit>
#include <QMessageBox>
#include <QListWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QDateTime>
#include <QTimer>

#include "inc/Library.h"
#include "inc/Member.h"
#include "inc/Librarian.h"
#include "inc/BookItem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Book Management Slots
    void on_addBookButton_clicked();
    void on_removeBookButton_clicked();
    void on_editBookButton_clicked();
    void on_searchBookButton_clicked();
    void on_refreshBooksButton_clicked();

    // Member Management Slots
    void on_registerMemberButton_clicked();
    void on_cancelMembershipButton_clicked();
    void on_searchMemberButton_clicked();
    void on_refreshMembersButton_clicked();

    // Book Operations Slots
    void on_checkoutBookButton_clicked();
    void on_returnBookButton_clicked();
    void on_renewBookButton_clicked();
    void on_reserveBookButton_clicked();

    // Fine Management Slots
    void on_payFineButton_clicked();
    void on_checkFinesButton_clicked();

    // Tab Change Slots
    void on_tabWidget_currentChanged(int index);

    // Timer for overdue check
    void checkOverdueBooks();

private:
    Ui::MainWindow *ui;
    Library library;
    Librarian librarian;
    
    // UI Setup methods
    void setupBookManagementTab();
    void setupMemberManagementTab();
    void setupBookOperationsTab();
    void setupFineManagementTab();
    void setupNotificationsTab();
    
    // Helper methods
    void refreshBooksTable();
    void refreshMembersTable();
    void refreshTransactionsTable();
    void refreshFinesTable();
    void refreshNotificationsList();
    
    // Utility methods
    void showMessage(const QString &title, const QString &message, QMessageBox::Icon icon = QMessageBox::Information);
    void logNotification(const QString &message);
    void clearBookForm();
    void clearMemberForm();
    void clearOperationForm();
    
    // Timer for periodic checks
    QTimer *overdueTimer;
};

#endif // MAINWINDOW_H 