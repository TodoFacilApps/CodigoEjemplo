import requests

def ConsumirServicio(tnTipoServicio, lcComerceID, lnMoneda, lnTelefono, lcNombreUsuario, lnCiNit,
                     lcNroPago, lnMontoClienteEmpresa, lcCorreo, lcUrlCallBack, lcUrlReturn, laPedidoDetalle):
    lcUrl = ("https://serviciostigomoney.pagofacil.com.bo/api/servicio/generarqrv2" 
             if tnTipoServicio == 1 else "https://serviciostigomoney.pagofacil.com.bo/api/servicio/realizarpagotigomoneyv2")

    laBody = {
        "tcCommerceID": lcComerceID,
        "tnMoneda": lnMoneda,
        "tnTelefono": lnTelefono,
        'tcNombreUsuario': lcNombreUsuario,
        'tnCiNit': lnCiNit,
        'tcNroPago': lcNroPago,
        "tnMontoClienteEmpresa": lnMontoClienteEmpresa,
        "tcCorreo": lcCorreo,
        'tcUrlCallBack': lcUrlCallBack,
        "tcUrlReturn": lcUrlReturn,
        'taPedidoDetalle': laPedidoDetalle
    }

    laHeader = {'Accept': 'application/json'}
    loResponse = requests.post(lcUrl, headers=laHeader, json=laBody)
    laResult = loResponse.json()

    return laResult
