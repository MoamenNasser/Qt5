#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QApplication>
#include <QDateTime>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , librarian("Admin", "EMP001")
{
    ui->setupUi(this);
    
    // Set window title
    setWindowTitle("Library Management System");
    setMinimumSize(1200, 800);
    
    // Initialize timer for overdue checks
    overdueTimer = new QTimer(this);
    connect(overdueTimer, &QTimer::timeout, this, &MainWindow::checkOverdueBooks);
    overdueTimer->start(60000); // Check every minute
    
    // Setup all tabs
    setupBookManagementTab();
    setupMemberManagementTab();
    setupBookOperationsTab();
    setupFineManagementTab();
    setupNotificationsTab();
    
    // Add some sample data
    addSampleData();
    
    // Initial refresh
    refreshBooksTable();
    refreshMembersTable();
    refreshTransactionsTable();
    refreshFinesTable();
    refreshNotificationsList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupBookManagementTab()
{
    // Book form group
    QGroupBox *bookFormGroup = new QGroupBox("Add/Edit Book");
    QGridLayout *bookFormLayout = new QGridLayout();
    
    bookFormLayout->addWidget(new QLabel("Author:"), 0, 0);
    ui->authorLineEdit = new QLineEdit();
    bookFormLayout->addWidget(ui->authorLineEdit, 0, 1);
    
    bookFormLayout->addWidget(new QLabel("Title:"), 1, 0);
    ui->titleLineEdit = new QLineEdit();
    bookFormLayout->addWidget(ui->titleLineEdit, 1, 1);
    
    bookFormLayout->addWidget(new QLabel("Subject:"), 2, 0);
    ui->subjectLineEdit = new QLineEdit();
    bookFormLayout->addWidget(ui->subjectLineEdit, 2, 1);
    
    bookFormLayout->addWidget(new QLabel("Publication Date:"), 3, 0);
    ui->publicationDateLineEdit = new QLineEdit();
    bookFormLayout->addWidget(ui->publicationDateLineEdit, 3, 1);
    
    bookFormLayout->addWidget(new QLabel("Barcode:"), 4, 0);
    ui->barcodeLineEdit = new QLineEdit();
    bookFormLayout->addWidget(ui->barcodeLineEdit, 4, 1);
    
    bookFormLayout->addWidget(new QLabel("Rack Number:"), 5, 0);
    ui->rackNumberSpinBox = new QSpinBox();
    ui->rackNumberSpinBox->setRange(1, 100);
    bookFormLayout->addWidget(ui->rackNumberSpinBox, 5, 1);
    
    QHBoxLayout *bookButtonsLayout = new QHBoxLayout();
    ui->addBookButton = new QPushButton("Add Book");
    ui->editBookButton = new QPushButton("Edit Book");
    ui->removeBookButton = new QPushButton("Remove Book");
    ui->searchBookButton = new QPushButton("Search");
    ui->refreshBooksButton = new QPushButton("Refresh");
    
    bookButtonsLayout->addWidget(ui->addBookButton);
    bookButtonsLayout->addWidget(ui->editBookButton);
    bookButtonsLayout->addWidget(ui->removeBookButton);
    bookButtonsLayout->addWidget(ui->searchBookButton);
    bookButtonsLayout->addWidget(ui->refreshBooksButton);
    
    bookFormLayout->addLayout(bookButtonsLayout, 6, 0, 1, 2);
    bookFormGroup->setLayout(bookFormLayout);
    
    // Books table
    ui->booksTable = new QTableWidget();
    ui->booksTable->setColumnCount(7);
    ui->booksTable->setHorizontalHeaderLabels({"Barcode", "Title", "Author", "Subject", "Publication Date", "Rack", "Status"});
    ui->booksTable->horizontalHeader()->setStretchLastSection(true);
    ui->booksTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    QVBoxLayout *bookTabLayout = new QVBoxLayout();
    bookTabLayout->addWidget(bookFormGroup);
    bookTabLayout->addWidget(ui->booksTable);
    
    QWidget *bookTab = new QWidget();
    bookTab->setLayout(bookTabLayout);
    ui->tabWidget->addTab(bookTab, "Book Management");
}

void MainWindow::setupMemberManagementTab()
{
    // Member form group
    QGroupBox *memberFormGroup = new QGroupBox("Register Member");
    QGridLayout *memberFormLayout = new QGridLayout();
    
    memberFormLayout->addWidget(new QLabel("Name:"), 0, 0);
    ui->memberNameLineEdit = new QLineEdit();
    memberFormLayout->addWidget(ui->memberNameLineEdit, 0, 1);
    
    memberFormLayout->addWidget(new QLabel("Member ID:"), 1, 0);
    ui->memberIDLineEdit = new QLineEdit();
    memberFormLayout->addWidget(ui->memberIDLineEdit, 1, 1);
    
    memberFormLayout->addWidget(new QLabel("Email:"), 2, 0);
    ui->memberEmailLineEdit = new QLineEdit();
    memberFormLayout->addWidget(ui->memberEmailLineEdit, 2, 1);
    
    memberFormLayout->addWidget(new QLabel("Phone:"), 3, 0);
    ui->memberPhoneLineEdit = new QLineEdit();
    memberFormLayout->addWidget(ui->memberPhoneLineEdit, 3, 1);
    
    QHBoxLayout *memberButtonsLayout = new QHBoxLayout();
    ui->registerMemberButton = new QPushButton("Register Member");
    ui->cancelMembershipButton = new QPushButton("Cancel Membership");
    ui->searchMemberButton = new QPushButton("Search");
    ui->refreshMembersButton = new QPushButton("Refresh");
    
    memberButtonsLayout->addWidget(ui->registerMemberButton);
    memberButtonsLayout->addWidget(ui->cancelMembershipButton);
    memberButtonsLayout->addWidget(ui->searchMemberButton);
    memberButtonsLayout->addWidget(ui->refreshMembersButton);
    
    memberFormLayout->addLayout(memberButtonsLayout, 4, 0, 1, 2);
    memberFormGroup->setLayout(memberFormLayout);
    
    // Members table
    ui->membersTable = new QTableWidget();
    ui->membersTable->setColumnCount(5);
    ui->membersTable->setHorizontalHeaderLabels({"Member ID", "Name", "Email", "Phone", "Fine Balance"});
    ui->membersTable->horizontalHeader()->setStretchLastSection(true);
    ui->membersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    QVBoxLayout *memberTabLayout = new QVBoxLayout();
    memberTabLayout->addWidget(memberFormGroup);
    memberTabLayout->addWidget(ui->membersTable);
    
    QWidget *memberTab = new QWidget();
    memberTab->setLayout(memberTabLayout);
    ui->tabWidget->addTab(memberTab, "Member Management");
}

void MainWindow::setupBookOperationsTab()
{
    // Operations form group
    QGroupBox *operationFormGroup = new QGroupBox("Book Operations");
    QGridLayout *operationFormLayout = new QGridLayout();
    
    operationFormLayout->addWidget(new QLabel("Member ID:"), 0, 0);
    ui->operationMemberIDLineEdit = new QLineEdit();
    operationFormLayout->addWidget(ui->operationMemberIDLineEdit, 0, 1);
    
    operationFormLayout->addWidget(new QLabel("Book Barcode:"), 1, 0);
    ui->operationBarcodeLineEdit = new QLineEdit();
    operationFormLayout->addWidget(ui->operationBarcodeLineEdit, 1, 1);
    
    QHBoxLayout *operationButtonsLayout = new QHBoxLayout();
    ui->checkoutBookButton = new QPushButton("Checkout Book");
    ui->returnBookButton = new QPushButton("Return Book");
    ui->renewBookButton = new QPushButton("Renew Book");
    ui->reserveBookButton = new QPushButton("Reserve Book");
    
    operationButtonsLayout->addWidget(ui->checkoutBookButton);
    operationButtonsLayout->addWidget(ui->returnBookButton);
    operationButtonsLayout->addWidget(ui->renewBookButton);
    operationButtonsLayout->addWidget(ui->reserveBookButton);
    
    operationFormLayout->addLayout(operationButtonsLayout, 2, 0, 1, 2);
    operationFormGroup->setLayout(operationFormLayout);
    
    // Transactions table
    ui->transactionsTable = new QTableWidget();
    ui->transactionsTable->setColumnCount(4);
    ui->transactionsTable->setHorizontalHeaderLabels({"Member ID", "Book Barcode", "Due Date", "Status"});
    ui->transactionsTable->horizontalHeader()->setStretchLastSection(true);
    ui->transactionsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    QVBoxLayout *operationTabLayout = new QVBoxLayout();
    operationTabLayout->addWidget(operationFormGroup);
    operationTabLayout->addWidget(ui->transactionsTable);
    
    QWidget *operationTab = new QWidget();
    operationTab->setLayout(operationTabLayout);
    ui->tabWidget->addTab(operationTab, "Book Operations");
}

void MainWindow::setupFineManagementTab()
{
    // Fine form group
    QGroupBox *fineFormGroup = new QGroupBox("Fine Management");
    QGridLayout *fineFormLayout = new QGridLayout();
    
    fineFormLayout->addWidget(new QLabel("Member ID:"), 0, 0);
    ui->fineMemberIDLineEdit = new QLineEdit();
    fineFormLayout->addWidget(ui->fineMemberIDLineEdit, 0, 1);
    
    fineFormLayout->addWidget(new QLabel("Amount:"), 1, 0);
    ui->fineAmountLineEdit = new QLineEdit();
    fineFormLayout->addWidget(ui->fineAmountLineEdit, 1, 1);
    
    QHBoxLayout *fineButtonsLayout = new QHBoxLayout();
    ui->payFineButton = new QPushButton("Pay Fine");
    ui->checkFinesButton = new QPushButton("Check Fines");
    
    fineButtonsLayout->addWidget(ui->payFineButton);
    fineButtonsLayout->addWidget(ui->checkFinesButton);
    
    fineFormLayout->addLayout(fineButtonsLayout, 2, 0, 1, 2);
    fineFormGroup->setLayout(fineFormLayout);
    
    // Fines table
    ui->finesTable = new QTableWidget();
    ui->finesTable->setColumnCount(3);
    ui->finesTable->setHorizontalHeaderLabels({"Member ID", "Member Name", "Fine Balance"});
    ui->finesTable->horizontalHeader()->setStretchLastSection(true);
    ui->finesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    QVBoxLayout *fineTabLayout = new QVBoxLayout();
    fineTabLayout->addWidget(fineFormGroup);
    fineTabLayout->addWidget(ui->finesTable);
    
    QWidget *fineTab = new QWidget();
    fineTab->setLayout(fineTabLayout);
    ui->tabWidget->addTab(fineTab, "Fine Management");
}

void MainWindow::setupNotificationsTab()
{
    // Notifications list
    ui->notificationsList = new QListWidget();
    
    QVBoxLayout *notificationTabLayout = new QVBoxLayout();
    notificationTabLayout->addWidget(new QLabel("System Notifications:"));
    notificationTabLayout->addWidget(ui->notificationsList);
    
    QWidget *notificationTab = new QWidget();
    notificationTab->setLayout(notificationTabLayout);
    ui->tabWidget->addTab(notificationTab, "Notifications");
}

void MainWindow::addSampleData()
{
    // Add sample books
    BookItem book1("George Orwell", "1984", "Dystopian", "1949", "B001", "BC001", true, 1);
    BookItem book2("J.R.R. Tolkien", "The Hobbit", "Fantasy", "1937", "B002", "BC002", true, 1);
    BookItem book3("Bjarne Stroustrup", "C++ Programming", "Programming", "1997", "B003", "BC003", true, 2);
    
    librarian.addBook(library, book1);
    librarian.addBook(library, book2);
    librarian.addBook(library, book3);
    
    // Add sample members
    Member member1("John Doe", "M001", "john.doe@example.com", "1234567890");
    Member member2("Jane Smith", "M002", "jane.smith@example.com", "0987654321");
    
    library.registerMember(member1);
    library.registerMember(member2);
    
    logNotification("Library Management System initialized with sample data.");
}

// Book Management Slots
void MainWindow::on_addBookButton_clicked()
{
    QString author = ui->authorLineEdit->text();
    QString title = ui->titleLineEdit->text();
    QString subject = ui->subjectLineEdit->text();
    QString pubDate = ui->publicationDateLineEdit->text();
    QString barcode = ui->barcodeLineEdit->text();
    int rackNumber = ui->rackNumberSpinBox->value();
    
    if (author.isEmpty() || title.isEmpty() || barcode.isEmpty()) {
        showMessage("Error", "Please fill in all required fields (Author, Title, Barcode)", QMessageBox::Warning);
        return;
    }
    
    BookItem book(author.toStdString(), title.toStdString(), subject.toStdString(), 
                  pubDate.toStdString(), "B" + barcode.toStdString(), barcode.toStdString(), true, rackNumber);
    
    librarian.addBook(library, book);
    refreshBooksTable();
    clearBookForm();
    logNotification("Book added: " + title);
    showMessage("Success", "Book added successfully!");
}

void MainWindow::on_removeBookButton_clicked()
{
    int currentRow = ui->booksTable->currentRow();
    if (currentRow < 0) {
        showMessage("Error", "Please select a book to remove", QMessageBox::Warning);
        return;
    }
    
    QString barcode = ui->booksTable->item(currentRow, 0)->text();
    librarian.removeBook(library, barcode.toStdString());
    refreshBooksTable();
    logNotification("Book removed: " + barcode);
    showMessage("Success", "Book removed successfully!");
}

void MainWindow::on_editBookButton_clicked()
{
    int currentRow = ui->booksTable->currentRow();
    if (currentRow < 0) {
        showMessage("Error", "Please select a book to edit", QMessageBox::Warning);
        return;
    }
    
    QString barcode = ui->booksTable->item(currentRow, 0)->text();
    QString author = ui->authorLineEdit->text();
    QString title = ui->titleLineEdit->text();
    QString subject = ui->subjectLineEdit->text();
    QString pubDate = ui->publicationDateLineEdit->text();
    int rackNumber = ui->rackNumberSpinBox->value();
    
    if (author.isEmpty() || title.isEmpty()) {
        showMessage("Error", "Please fill in Author and Title fields", QMessageBox::Warning);
        return;
    }
    
    librarian.editBook(library, barcode.toStdString(), author.toStdString(), title.toStdString(),
                       subject.toStdString(), pubDate.toStdString(), rackNumber);
    refreshBooksTable();
    clearBookForm();
    logNotification("Book edited: " + title);
    showMessage("Success", "Book updated successfully!");
}

void MainWindow::on_searchBookButton_clicked()
{
    QString title = ui->titleLineEdit->text();
    QString author = ui->authorLineEdit->text();
    QString subject = ui->subjectLineEdit->text();
    QString pubDate = ui->publicationDateLineEdit->text();
    
    // Clear table first
    ui->booksTable->setRowCount(0);
    
    // Search in library (this would need to be implemented in the Library class)
    // For now, we'll just refresh the table
    refreshBooksTable();
    logNotification("Book search performed");
}

void MainWindow::on_refreshBooksButton_clicked()
{
    refreshBooksTable();
}

// Member Management Slots
void MainWindow::on_registerMemberButton_clicked()
{
    QString name = ui->memberNameLineEdit->text();
    QString memberID = ui->memberIDLineEdit->text();
    QString email = ui->memberEmailLineEdit->text();
    QString phone = ui->memberPhoneLineEdit->text();
    
    if (name.isEmpty() || memberID.isEmpty()) {
        showMessage("Error", "Please fill in Name and Member ID fields", QMessageBox::Warning);
        return;
    }
    
    Member member(name.toStdString(), memberID.toStdString(), email.toStdString(), phone.toStdString());
    library.registerMember(member);
    refreshMembersTable();
    clearMemberForm();
    logNotification("Member registered: " + name);
    showMessage("Success", "Member registered successfully!");
}

void MainWindow::on_cancelMembershipButton_clicked()
{
    int currentRow = ui->membersTable->currentRow();
    if (currentRow < 0) {
        showMessage("Error", "Please select a member to cancel membership", QMessageBox::Warning);
        return;
    }
    
    QString memberID = ui->membersTable->item(currentRow, 0)->text();
    library.cancelMembership(memberID.toStdString());
    refreshMembersTable();
    logNotification("Membership cancelled for: " + memberID);
    showMessage("Success", "Membership cancelled successfully!");
}

void MainWindow::on_searchMemberButton_clicked()
{
    // Implementation for member search
    refreshMembersTable();
    logNotification("Member search performed");
}

void MainWindow::on_refreshMembersButton_clicked()
{
    refreshMembersTable();
}

// Book Operations Slots
void MainWindow::on_checkoutBookButton_clicked()
{
    QString memberID = ui->operationMemberIDLineEdit->text();
    QString barcode = ui->operationBarcodeLineEdit->text();
    
    if (memberID.isEmpty() || barcode.isEmpty()) {
        showMessage("Error", "Please fill in Member ID and Book Barcode", QMessageBox::Warning);
        return;
    }
    
    if (library.checkoutBook(memberID.toStdString(), barcode.toStdString())) {
        refreshTransactionsTable();
        refreshBooksTable();
        clearOperationForm();
        logNotification("Book checked out: " + barcode + " by " + memberID);
        showMessage("Success", "Book checked out successfully!");
    } else {
        showMessage("Error", "Failed to checkout book. Check if book is available and member is eligible.", QMessageBox::Warning);
    }
}

void MainWindow::on_returnBookButton_clicked()
{
    QString memberID = ui->operationMemberIDLineEdit->text();
    QString barcode = ui->operationBarcodeLineEdit->text();
    
    if (memberID.isEmpty() || barcode.isEmpty()) {
        showMessage("Error", "Please fill in Member ID and Book Barcode", QMessageBox::Warning);
        return;
    }
    
    if (library.returnBook(memberID.toStdString(), barcode.toStdString())) {
        refreshTransactionsTable();
        refreshBooksTable();
        refreshFinesTable();
        clearOperationForm();
        logNotification("Book returned: " + barcode + " by " + memberID);
        showMessage("Success", "Book returned successfully!");
    } else {
        showMessage("Error", "Failed to return book. Check if book was checked out by this member.", QMessageBox::Warning);
    }
}

void MainWindow::on_renewBookButton_clicked()
{
    QString memberID = ui->operationMemberIDLineEdit->text();
    QString barcode = ui->operationBarcodeLineEdit->text();
    
    if (memberID.isEmpty() || barcode.isEmpty()) {
        showMessage("Error", "Please fill in Member ID and Book Barcode", QMessageBox::Warning);
        return;
    }
    
    if (library.renewBook(memberID.toStdString(), barcode.toStdString())) {
        refreshTransactionsTable();
        clearOperationForm();
        logNotification("Book renewed: " + barcode + " by " + memberID);
        showMessage("Success", "Book renewed successfully!");
    } else {
        showMessage("Error", "Failed to renew book. Check if book was checked out by this member.", QMessageBox::Warning);
    }
}

void MainWindow::on_reserveBookButton_clicked()
{
    QString memberID = ui->operationMemberIDLineEdit->text();
    QString barcode = ui->operationBarcodeLineEdit->text();
    
    if (memberID.isEmpty() || barcode.isEmpty()) {
        showMessage("Error", "Please fill in Member ID and Book Barcode", QMessageBox::Warning);
        return;
    }
    
    if (library.reserveBook(memberID.toStdString(), barcode.toStdString())) {
        clearOperationForm();
        logNotification("Book reserved: " + barcode + " by " + memberID);
        showMessage("Success", "Book reserved successfully!");
    } else {
        showMessage("Error", "Failed to reserve book. Check if book exists and member can reserve.", QMessageBox::Warning);
    }
}

// Fine Management Slots
void MainWindow::on_payFineButton_clicked()
{
    QString memberID = ui->fineMemberIDLineEdit->text();
    QString amountStr = ui->fineAmountLineEdit->text();
    
    if (memberID.isEmpty() || amountStr.isEmpty()) {
        showMessage("Error", "Please fill in Member ID and Amount", QMessageBox::Warning);
        return;
    }
    
    bool ok;
    double amount = amountStr.toDouble(&ok);
    if (!ok) {
        showMessage("Error", "Please enter a valid amount", QMessageBox::Warning);
        return;
    }
    
    auto memberIt = library.members.find(memberID.toStdString());
    if (memberIt != library.members.end()) {
        if (memberIt->second.payFine(amount)) {
            refreshFinesTable();
            ui->fineAmountLineEdit->clear();
            logNotification("Fine paid: $" + QString::number(amount) + " by " + memberID);
            showMessage("Success", "Fine paid successfully!");
        } else {
            showMessage("Error", "Failed to pay fine. Check the amount.", QMessageBox::Warning);
        }
    } else {
        showMessage("Error", "Member not found", QMessageBox::Warning);
    }
}

void MainWindow::on_checkFinesButton_clicked()
{
    refreshFinesTable();
    logNotification("Fines checked");
}

// Tab Change Slots
void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch(index) {
        case 0: // Book Management
            refreshBooksTable();
            break;
        case 1: // Member Management
            refreshMembersTable();
            break;
        case 2: // Book Operations
            refreshTransactionsTable();
            break;
        case 3: // Fine Management
            refreshFinesTable();
            break;
        case 4: // Notifications
            refreshNotificationsList();
            break;
    }
}

// Timer for overdue check
void MainWindow::checkOverdueBooks()
{
    library.overdueCheck();
    refreshTransactionsTable();
    refreshFinesTable();
}

// Helper methods
void MainWindow::refreshBooksTable()
{
    ui->booksTable->setRowCount(0);
    int row = 0;
    
    for (const auto& bookPair : library.books) {
        const BookItem& book = bookPair.second;
        ui->booksTable->insertRow(row);
        
        ui->booksTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(book.Barcode)));
        ui->booksTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(book.title)));
        ui->booksTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(book.author)));
        ui->booksTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(book.subject)));
        ui->booksTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(book.DateOfPublication)));
        ui->booksTable->setItem(row, 5, new QTableWidgetItem(QString::number(book.rackNumber)));
        ui->booksTable->setItem(row, 6, new QTableWidgetItem(book.InStock ? "Available" : "Checked Out"));
        
        row++;
    }
}

void MainWindow::refreshMembersTable()
{
    ui->membersTable->setRowCount(0);
    int row = 0;
    
    for (const auto& memberPair : library.members) {
        const Member& member = memberPair.second;
        ui->membersTable->insertRow(row);
        
        ui->membersTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(member.getMemberID())));
        ui->membersTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(member.getName())));
        ui->membersTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(member.getEmail())));
        ui->membersTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(member.getPhoneNumber())));
        ui->membersTable->setItem(row, 4, new QTableWidgetItem(QString::number(member.getFineBalance())));
        
        row++;
    }
}

void MainWindow::refreshTransactionsTable()
{
    ui->transactionsTable->setRowCount(0);
    int row = 0;
    
    for (const auto& transaction : library.transactions) {
        ui->transactionsTable->insertRow(row);
        
        ui->transactionsTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(transaction.memberID)));
        ui->transactionsTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(transaction.bookBarcode)));
        
        QDateTime dueDate = QDateTime::fromSecsSinceEpoch(transaction.dueDate);
        ui->transactionsTable->setItem(row, 2, new QTableWidgetItem(dueDate.toString("yyyy-MM-dd hh:mm:ss")));
        
        QDateTime now = QDateTime::currentDateTime();
        QString status = (dueDate < now) ? "Overdue" : "Active";
        ui->transactionsTable->setItem(row, 3, new QTableWidgetItem(status));
        
        row++;
    }
}

void MainWindow::refreshFinesTable()
{
    ui->finesTable->setRowCount(0);
    int row = 0;
    
    for (const auto& memberPair : library.members) {
        const Member& member = memberPair.second;
        if (member.getFineBalance() > 0) {
            ui->finesTable->insertRow(row);
            
            ui->finesTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(member.getMemberID())));
            ui->finesTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(member.getName())));
            ui->finesTable->setItem(row, 2, new QTableWidgetItem(QString::number(member.getFineBalance())));
            
            row++;
        }
    }
}

void MainWindow::refreshNotificationsList()
{
    // This would typically load from a notification log
    // For now, we'll just keep the current notifications
}

// Utility methods
void MainWindow::showMessage(const QString &title, const QString &message, QMessageBox::Icon icon)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    msgBox.setIcon(icon);
    msgBox.exec();
}

void MainWindow::logNotification(const QString &message)
{
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString logEntry = "[" + timestamp + "] " + message;
    ui->notificationsList->addItem(logEntry);
    ui->notificationsList->scrollToBottom();
}

void MainWindow::clearBookForm()
{
    ui->authorLineEdit->clear();
    ui->titleLineEdit->clear();
    ui->subjectLineEdit->clear();
    ui->publicationDateLineEdit->clear();
    ui->barcodeLineEdit->clear();
    ui->rackNumberSpinBox->setValue(1);
}

void MainWindow::clearMemberForm()
{
    ui->memberNameLineEdit->clear();
    ui->memberIDLineEdit->clear();
    ui->memberEmailLineEdit->clear();
    ui->memberPhoneLineEdit->clear();
}

void MainWindow::clearOperationForm()
{
    ui->operationMemberIDLineEdit->clear();
    ui->operationBarcodeLineEdit->clear();
} 