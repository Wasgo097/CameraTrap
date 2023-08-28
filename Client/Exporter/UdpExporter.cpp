#include "UdpExporter.h"

UdpExporter::UdpExporter(UdpExporterSettings settings) :_settings{ std::move(settings) }/*, _socket{ _ioContext }*/
{
	asio::ip::udp::resolver resolver(_ioContext);
	_endpoint = *resolver.resolve(_settings.serverIp, _settings.serverPort).begin();
	//_socket.open();
}

bool UdpExporter::ExportData(const MoveDetectionResult& dataToExport)
{
	return false;
}