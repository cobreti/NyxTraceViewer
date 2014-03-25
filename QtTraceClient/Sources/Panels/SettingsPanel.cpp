#include "SettingsPanel.h"
#include "ui_SettingsPanel.h"
#include "MainWindow/TcpIpSettingsPanel.h"


#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QScriptEngine>


CSettingsPanel::CSettingsPanel() : QWidget(),
    ui(new Ui::SettingsPanel()),
    m_pTxtTcpIpSettingsPanel(NULL)
{
    ui->setupUi(this);

    Init();
}


CSettingsPanel::~CSettingsPanel()
{

}


void CSettingsPanel::onTraceDirectoryServerChanged(const QString& text)
{
    ui->applyButton->setEnabled(true);
}


void CSettingsPanel::onApply()
{
    QUrl url("http://10.11.0.180/backend/");
    QString method = "Management/Services/ListUsers.php";

    url.setPath( QString("%1%2").arg(url.path()).arg(method));

    QMap<QString, QVariant> params;
    params["key"] = "53850c682a15401eab4d66864c5600c0";

    QUrlQuery   query;
    foreach(QString param, params.keys())
    {
        query.addQueryItem(param, params[param].toString());
    }
    url.setQuery(query);

    QNetworkRequest request;
    request.setUrl(url);

    QString urlstr = url.toString();

    connect( &networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResult(QNetworkReply*)));

    QByteArray      data;
    data.append("key=53850c682a15401eab4d66864c5600c0");
    currentReply = networkManager.post(request, data);
}


void CSettingsPanel::onResult(QNetworkReply *reply)
{
    if (currentReply->error() != QNetworkReply::NoError)
        return;

    QString data = reply->readAll();

    QScriptEngine engine;
    QScriptValue result = engine.evaluate(data);
}


void CSettingsPanel::Init()
{
    m_pTxtTcpIpSettingsPanel = new CTcpIpSettingsPanel();
    m_pTxtTcpIpSettingsPanel->SetTracesReceiversSvr( &TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceiversSvr(1) );
    ui->TxtTracePortLayout->addWidget(m_pTxtTcpIpSettingsPanel);

    connect( ui->TraceDirectoryServer, SIGNAL(textChanged(QString)), this, SLOT(onTraceDirectoryServerChanged(QString)));
    connect( ui->applyButton, SIGNAL(clicked()), this, SLOT(onApply()));
}


void CSettingsPanel::showEvent(QShowEvent *)
{
    ui->applyButton->setEnabled(false);
}


void CSettingsPanel::hideEvent(QHideEvent *)
{

}

