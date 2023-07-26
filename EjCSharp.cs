using System;
using System.Collections.Generic;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;

public async Task<object> RecolectarDatos(string tnTelefono, string tcRazonSocial, string tcCiNit, decimal tnMonto, string tcCorreo, int tnTipoServicio, List<object> taPedidoDetalle)
{
    try
    {
        string lcComerceID = "";
        int lnMoneda = 2;
        string lcNroPago = "test-" + new Random().Next(100000, 999999);
        string lcUrlCallBack = "http://localhost:8000/";
        string lcUrlReturn = "http://localhost:8000/";
        string lcUrl = "";

        HttpClient client = new HttpClient();

        if (tnTipoServicio == 1)
        {
            lcUrl = "https://serviciostigomoney.pagofacil.com.bo/api/servicio/generarqrv2";
        }
        else if (tnTipoServicio == 2)
        {
            lcUrl = "https://serviciostigomoney.pagofacil.com.bo/api/servicio/realizarpagotigomoneyv2";
        }

        client.DefaultRequestHeaders.Accept.Clear();
        client.DefaultRequestHeaders.Accept.Add(new System.Net.Http.Headers.MediaTypeWithQualityHeaderValue("application/json"));

        var laBody = new
        {
            tcCommerceID = lcComerceID,
            tnMoneda = lnMoneda,
            tnTelefono,
            tcNombreUsuario = tcRazonSocial,
            tnCiNit = tcCiNit,
            tcNroPago = lcNroPago,
            tnMontoClienteEmpresa = tnMonto,
            tcCorreo,
            tcUrlCallBack = lcUrlCallBack,
            tcUrlReturn = lcUrlReturn,
            taPedidoDetalle
        };

        string jsonBody = Newtonsoft.Json.JsonConvert.SerializeObject(laBody);

        var content = new StringContent(jsonBody, Encoding.UTF8, "application/json");

        HttpResponseMessage response = await client.PostAsync(lcUrl, content);

        if (response.IsSuccessStatusCode)
        {
            string jsonResponse = await response.Content.ReadAsStringAsync();
            object laResult = Newtonsoft.Json.JsonConvert.DeserializeObject(jsonResponse);
            return laResult;
        }
        else
        {
            return response.ReasonPhrase;
        }
    }
    catch (Exception ex)
    {
        return ex.Message + " - " + ex.LineNumber; 
    }
}
