const axios = require("axios");

const loClient = axios.create({
  headers: {
    Accept: "application/json",
  },
});

async function sendRequest(
  tnTipoServicio,
  tcCommerceID,
  tnMoneda,
  tnTelefono,
  tcNombreUsuario,
  tnCiNit,
  tcNroPago,
  tnMontoClienteEmpresa,
  tcCorreo,
  tcUrlCallBack,
  tcUrlReturn,
  taPedidoDetalle
) {
  let lcUrl;

  if (tnTipoServicio === 1) {
    lcUrl =
      "https://serviciostigomoney.pagofacil.com.bo/api/servicio/generarqrv2";
  } else if (tnTipoServicio === 2) {
    lcUrl =
      "https://serviciostigomoney.pagofacil.com.bo/api/servicio/realizarpagotigomoneyv2";
  }

  const laBody = {
    tcCommerceID,
    tnMoneda,
    tnTelefono,
    tcNombreUsuario,
    tnCiNit,
    tcNroPago,
    tnMontoClienteEmpresa,
    tcCorreo,
    tcUrlCallBack,
    tcUrlReturn,
    taPedidoDetalle,
  };

  const loResponse = await loClient.post(lcUrl, laBody);

  const laResult = loResponse.data;

  return laResult;
}
