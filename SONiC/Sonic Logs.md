Yes — in SONiC (and in general Linux with Docker), **container logs are visible on the host machine**. Here’s how it works:

---

## 🧩 How Docker Logging Works in SONiC

- **Default logging driver**: By default, Docker uses the `json-file` logging driver.
    - This means logs from processes inside a container are written to JSON files on the host.
    - Location: `/var/lib/docker/containers/<container_id>/<container_id>-json.log`
- **SONiC integration**:
    - SONiC services (like `swss`, `bgp`, `syncd`) run inside Docker containers.
    - Their logs are written both to the container log files **and** to SONiC’s `/var/log/` directory on the host.
    - Example: `/var/log/swss/swss.log` is accessible directly on the host, even though `swss` runs inside a container.
- **Syslog forwarding**:
    - Many SONiC containers forward logs to the host’s syslog (`/var/log/syslog`).
    - This allows centralized log collection and makes troubleshooting easier without needing to `docker exec` into each container.

---
## ⚡ Practical Ways to See Logs

- **On the host (outside Docker)**
```bash
    tail -f /var/log/swss/swss.log
    tail -f /var/log/syslog
    ```
- **From Docker directly**
```bash
    docker logs swss
    docker logs bgp
    ```

---

## ✅ Key Takeaway

Yes — SONiC containers write logs to the host machine. You can see them in `/var/log/` and via `docker logs`. This dual logging setup ensures you don’t have to enter containers just to troubleshoot.

---

Would you like me to show you a **map of the most important SONiC containers and which host log files they write to**? That way you’ll know exactly where to look depending on the service you’re debugging.