# 17

Step 2: Select three hosts on the internet from different regions: one in North America, one in Asia, and one in Europe. Conduct a ping experiment with varying packet sizes and analyze the results.

- Use the ping command to send packets of varying sizes (e.g., 32 bytes, 128 bytes, 512 bytes, 1024 bytes). Use ping -s <size> <host>
- For each host, record the Packet Loss (the percentage of packets lost during the ping test) and the Round-Trip Time (RTT) (minimum, maximum, and average) RTT values.
- Compare the RTT values and packet loss for the three hosts and discuss how the geographical distance between your location and the hosts affects these measurements.

---

Using EC2 instances of AWS since those are easy to ping and know where they are.

```sh
HOSTS="ec2.us-east-1.amazonaws.com ec2.eu-central-1.amazonaws.com ec2.ap-northeast-1.amazonaws.com"
SIZES="32 128 512 1024"

for host in $HOSTS; do
  echo "===== Pinging $host ====="
  for size in $SIZES; do
    echo "--- Packet size: $size bytes ---"
    ping -s $size -c 5 $host
    echo
  done
done
# NOTE, Asian AWS EC2 instance failed. Switching to `www.u-tokyo.ac.jp`
```

```sh
HOSTS="www.u-tokyo.ac.jp"
SIZES="32 128 512 1024"

for host in $HOSTS; do
  echo "===== Pinging $host ====="
  for size in $SIZES; do
    echo "--- Packet size: $size bytes ---"
    ping -s $size -c 5 $host
    echo
  done
done
# NOTE, this server failed too. Switching to `www.yahoo.co.jp`
```

```sh
HOSTS="www.yahoo.co.jp"
SIZES="32 128 512 1024"

for host in $HOSTS; do
  echo "===== Pinging $host ====="
  for size in $SIZES; do
    echo "--- Packet size: $size bytes ---"
    ping -s $size -c 5 $host
    echo
  done
done
# NOTE, this server failed too. Switching to `www.yahoo.co.jp`
```

Output:

```sh
===== Pinging ec2.us-east-1.amazonaws.com =====
--- Packet size: 32 bytes ---
PING ec2.us-east-1.amazonaws.com (54.239.29.8) 32(60) bytes of data.
40 bytes from 54.239.29.8: icmp_seq=1 ttl=243 time=76.4 ms
40 bytes from 54.239.29.8: icmp_seq=2 ttl=243 time=74.9 ms
40 bytes from 54.239.29.8: icmp_seq=3 ttl=243 time=78.3 ms
40 bytes from 54.239.29.8: icmp_seq=4 ttl=243 time=80.5 ms
40 bytes from 54.239.29.8: icmp_seq=5 ttl=243 time=77.0 ms

--- ec2.us-east-1.amazonaws.com ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 4006ms
rtt min/avg/max/mdev = 74.892/77.413/80.483/1.882 ms

--- Packet size: 128 bytes ---
PING ec2.us-east-1.amazonaws.com (54.239.29.8) 128(156) bytes of data.
136 bytes from 54.239.29.8: icmp_seq=1 ttl=243 time=82.6 ms
136 bytes from 54.239.29.8: icmp_seq=2 ttl=243 time=75.6 ms
136 bytes from 54.239.29.8: icmp_seq=3 ttl=243 time=75.4 ms
136 bytes from 54.239.29.8: icmp_seq=4 ttl=243 time=76.0 ms
136 bytes from 54.239.29.8: icmp_seq=5 ttl=243 time=74.2 ms

--- ec2.us-east-1.amazonaws.com ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 4007ms
rtt min/avg/max/mdev = 74.168/76.730/82.559/2.976 ms

--- Packet size: 512 bytes ---
PING ec2.us-east-1.amazonaws.com (54.239.29.8) 512(540) bytes of data.
520 bytes from 54.239.29.8: icmp_seq=1 ttl=243 time=79.5 ms
520 bytes from 54.239.29.8: icmp_seq=2 ttl=243 time=91.8 ms
520 bytes from 54.239.29.8: icmp_seq=3 ttl=243 time=76.4 ms
520 bytes from 54.239.29.8: icmp_seq=4 ttl=243 time=76.1 ms
520 bytes from 54.239.29.8: icmp_seq=5 ttl=243 time=83.1 ms

--- ec2.us-east-1.amazonaws.com ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 4007ms
rtt min/avg/max/mdev = 76.050/81.373/91.781/5.787 ms

--- Packet size: 1024 bytes ---
PING ec2.us-east-1.amazonaws.com (54.239.29.8) 1024(1052) bytes of data.
1032 bytes from 54.239.29.8: icmp_seq=1 ttl=243 time=82.1 ms
1032 bytes from 54.239.29.8: icmp_seq=2 ttl=243 time=77.1 ms
1032 bytes from 54.239.29.8: icmp_seq=3 ttl=243 time=77.3 ms
1032 bytes from 54.239.29.8: icmp_seq=4 ttl=243 time=78.4 ms
1032 bytes from 54.239.29.8: icmp_seq=5 ttl=243 time=77.9 ms

--- ec2.us-east-1.amazonaws.com ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 4005ms
rtt min/avg/max/mdev = 77.120/78.567/82.102/1.824 ms

===== Pinging ec2.eu-central-1.amazonaws.com =====
--- Packet size: 32 bytes ---
PING ec2.eu-central-1.amazonaws.com (52.94.141.15) 32(60) bytes of data.
40 bytes from 52.94.141.15: icmp_seq=1 ttl=235 time=169 ms
40 bytes from 52.94.141.15: icmp_seq=2 ttl=235 time=166 ms
40 bytes from 52.94.141.15: icmp_seq=3 ttl=235 time=163 ms
40 bytes from 52.94.141.15: icmp_seq=4 ttl=235 time=164 ms
40 bytes from 52.94.141.15: icmp_seq=5 ttl=235 time=166 ms

--- ec2.eu-central-1.amazonaws.com ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 4003ms
rtt min/avg/max/mdev = 162.959/165.318/168.771/2.037 ms

--- Packet size: 128 bytes ---
PING ec2.eu-central-1.amazonaws.com (52.94.141.15) 128(156) bytes of data.
136 bytes from 52.94.141.15: icmp_seq=1 ttl=235 time=165 ms
136 bytes from 52.94.141.15: icmp_seq=2 ttl=235 time=166 ms
136 bytes from 52.94.141.15: icmp_seq=3 ttl=235 time=163 ms
136 bytes from 52.94.141.15: icmp_seq=4 ttl=235 time=167 ms
136 bytes from 52.94.141.15: icmp_seq=5 ttl=235 time=166 ms

--- ec2.eu-central-1.amazonaws.com ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 4004ms
rtt min/avg/max/mdev = 163.205/165.520/167.001/1.290 ms

--- Packet size: 512 bytes ---
PING ec2.eu-central-1.amazonaws.com (52.94.141.15) 512(540) bytes of data.
520 bytes from 52.94.141.15: icmp_seq=1 ttl=235 time=168 ms
520 bytes from 52.94.141.15: icmp_seq=2 ttl=235 time=166 ms
520 bytes from 52.94.141.15: icmp_seq=3 ttl=235 time=164 ms
520 bytes from 52.94.141.15: icmp_seq=4 ttl=235 time=165 ms
520 bytes from 52.94.141.15: icmp_seq=5 ttl=235 time=169 ms

--- ec2.eu-central-1.amazonaws.com ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 4007ms
rtt min/avg/max/mdev = 164.007/166.346/168.531/1.796 ms

--- Packet size: 1024 bytes ---
PING ec2.eu-central-1.amazonaws.com (52.94.141.15) 1024(1052) bytes of data.
1032 bytes from 52.94.141.15: icmp_seq=1 ttl=235 time=168 ms
1032 bytes from 52.94.141.15: icmp_seq=2 ttl=235 time=168 ms
1032 bytes from 52.94.141.15: icmp_seq=3 ttl=235 time=171 ms
1032 bytes from 52.94.141.15: icmp_seq=4 ttl=235 time=170 ms
1032 bytes from 52.94.141.15: icmp_seq=5 ttl=235 time=175 ms

--- ec2.eu-central-1.amazonaws.com ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 4007ms
rtt min/avg/max/mdev = 168.252/170.374/174.514/2.313 ms

===== Pinging www.yahoo.co.jp =====
--- Packet size: 32 bytes ---
PING edge12.g.yimg.jp (124.83.184.124) 32(60) bytes of data.
40 bytes from 124.83.184.124: icmp_seq=1 ttl=50 time=123 ms
40 bytes from 124.83.184.124: icmp_seq=2 ttl=50 time=128 ms
40 bytes from 124.83.184.124: icmp_seq=3 ttl=50 time=123 ms
40 bytes from 124.83.184.124: icmp_seq=4 ttl=50 time=122 ms
40 bytes from 124.83.184.124: icmp_seq=5 ttl=50 time=125 ms

--- edge12.g.yimg.jp ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 4006ms
rtt min/avg/max/mdev = 122.276/124.369/128.288/2.136 ms

--- Packet size: 128 bytes ---
PING edge12.g.yimg.jp (124.83.184.124) 128(156) bytes of data.
136 bytes from 124.83.184.124: icmp_seq=1 ttl=50 time=125 ms
136 bytes from 124.83.184.124: icmp_seq=2 ttl=50 time=124 ms
136 bytes from 124.83.184.124: icmp_seq=3 ttl=50 time=122 ms
136 bytes from 124.83.184.124: icmp_seq=4 ttl=50 time=124 ms
136 bytes from 124.83.184.124: icmp_seq=5 ttl=50 time=124 ms

--- edge12.g.yimg.jp ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 4008ms
rtt min/avg/max/mdev = 121.744/123.638/125.410/1.160 ms

--- Packet size: 512 bytes ---
PING edge12.g.yimg.jp (124.83.184.124) 512(540) bytes of data.
520 bytes from 124.83.184.124: icmp_seq=1 ttl=50 time=123 ms
520 bytes from 124.83.184.124: icmp_seq=2 ttl=50 time=122 ms
520 bytes from 124.83.184.124: icmp_seq=3 ttl=50 time=124 ms
520 bytes from 124.83.184.124: icmp_seq=4 ttl=50 time=123 ms
520 bytes from 124.83.184.124: icmp_seq=5 ttl=50 time=126 ms

--- edge12.g.yimg.jp ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 4005ms
rtt min/avg/max/mdev = 121.790/123.574/125.879/1.345 ms

--- Packet size: 1024 bytes ---
PING edge12.g.yimg.jp (124.83.184.124) 1024(1052) bytes of data.
1032 bytes from 124.83.184.124: icmp_seq=1 ttl=50 time=130 ms
1032 bytes from 124.83.184.124: icmp_seq=2 ttl=50 time=125 ms
1032 bytes from 124.83.184.124: icmp_seq=3 ttl=50 time=123 ms
1032 bytes from 124.83.184.124: icmp_seq=4 ttl=50 time=126 ms
1032 bytes from 124.83.184.124: icmp_seq=5 ttl=50 time=124 ms

--- edge12.g.yimg.jp ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 4007ms
rtt min/avg/max/mdev = 122.697/125.407/129.861/2.503 ms
```
