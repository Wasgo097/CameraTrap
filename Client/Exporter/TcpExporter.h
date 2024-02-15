#pragma once
#include "Interfaces/IDetectionResultSerializer.h"
#include "Interfaces/IMoveDetectionResultExporter.h"
#include "Settings/TcpExporterSettings.h"
#include <asio.hpp>
#include <memory>
class TcpExporter :public IMoveDetectionResultExporter
{
public:
	TcpExporter(TcpExporterSettings settings, std::unique_ptr<IDetectionResultSerializer>&& pSerializer);
	void ExportData(const MoveDetectionResult& dataToExport) override;
protected:
	TcpExporterSettings _settings;
	asio::ip::tcp::endpoint _endpoint;
	asio::io_service _ioService;
	std::unique_ptr<asio::ip::tcp::socket> _pSocket;
	std::string _serializationBuffer;
	std::unique_ptr<IDetectionResultSerializer> _pSerializer;
};