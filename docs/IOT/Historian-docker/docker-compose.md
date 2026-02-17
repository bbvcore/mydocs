version: "3.9"

services:
  sqlserver:
    image: mcr.microsoft.com/mssql/server:2022-latest
    container_name: sqlserver-control
    hostname: sqlserver
    restart: unless-stopped
    networks:
      - monitoring_net
    ports:
      - "1433:1433"
    environment:
      ACCEPT_EULA: "Y"
      MSSQL_SA_PASSWORD: "Str0ng_Passw0rd!"
      MSSQL_PID: "Developer"
      TZ: "Europe/Madrid"
    volumes:
      - sqlserver_data:/var/opt/mssql

  nodered:
    image: nodered/node-red:latest
    container_name: nodered
    restart: unless-stopped
    networks:
      - monitoring_net
    ports:
      - "1880:1880"
    environment:
      TZ: "Europe/Madrid"
    depends_on:
      - sqlserver
    volumes:
      - nodered_data:/data

  grafana:
    image: grafana/grafana:latest
    container_name: grafana
    restart: unless-stopped
    networks:
      - monitoring_net
    ports:
      - "3000:3000"
    environment:
      GF_SECURITY_ADMIN_PASSWORD: "admin"
      TZ: "Europe/Madrid"
    depends_on:
      - sqlserver
    volumes:
      - grafana_data:/var/lib/grafana

volumes:
  sqlserver_data:
  nodered_data:
  grafana_data:

networks:
  monitoring_net:
    driver: bridge
