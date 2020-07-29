
## Merchant to vnpay

| Parameter | Required | Format | Min, Max | Example | Description |
| - | - | - | - | - | - |
| vnp_Version    | Yes | Alphanumeric | 1, 8    | 1                   | Current is 2.0.0 |
| vnp_Command    | Yes | Alpha        | 1, 16   | pay                 | "pay" |
| vnp_TmnCode    | Yes | Alphanumeric | 8       | VNPAY001            | merchant website on vnpay network |
| vnp_BankCode   | No  | Alpha        | 3, 20   | VIETCOMBANK         | mã ngân hàng thanh toán (merchant?) |
| vnp_Locale     | Yes | Alpha        | 2, 5    | vn/en               ||
| vnp_CurrCode   | Yes | Alpha        | 3       | VND                 | only VND for now (2015) |
| vnp_TxnRef     | Yes | Alphanumeric | 1, 100  | VNPAY123            | uuid, to differentiate between orders |
| vnp_OrderInfo  | Yes | Alphanumeric | 1, 255  | Nap 100K ..         | some description, vietnamese, no accented characters |
| vnp_OrderType  | Yes | Alpha        | 1, 100  | topup               | mã danh much hàng hoá. Aka order category, will be prodived at merchant vnpay page |
| vnp_Amount     | Yes | Numeric      | 1, 12   | 100000              | amount, 100x the vnd amount, so example is 10k VND |
| vnp_ReturnUrl  | Yes | Alphanumeric | 10, 255 | merchant.com/return | after successful transaction |
| vnp_IpAddr     | Yes | Alphanumeric | 7, 45   | 123.123.123.123     ||
| vnp_CreateDate | Yes | Numeric      | 14      | 20150924080900      ||
| vnp_SecureHash | Yes | Alphanumeric | 32, 256 | 2a4f22...           | checksum. Creating this depends on merchant configs and api version. SHA256 and MD5 |

## Vnpay response

| Parameter | Required | Format | Min, Max | Example | Description |
| - | - | - | - | - | - |
| vnp_TmnCode       | Yes | Alphanumeric | 8       | VNPAY001            | merchant website on vnpay network |
| vnp_TxnRef        | Yes | Alphanumeric | 1, 100  | VNPAY123            | uuid, to differentiate between orders |
| vnp_Amount        | Yes | Numeric      | 1, 12   | 100000              | amount, 100x the vnd amount, so example is 10k VND |
| vnp_OrderInfo     | Yes | Alphanumeric | 1, 255  | Nap 100K ..         | some description, vietnamese, no accented characters |
| vnp_ResponseCode  | Yes | Numeric      | 2       | 00                  | 00 for success for every api |
| vnp_BankCode      | No  | Alpha        | 3, 20   | VIETCOMBANK         | mã ngân hàng phát hành thẻ (client?) |
| vnp_BankTranNo    | No  | Alpha        | 3, 255  | 20160802055902      | mã giao dịch tại ngân hàng |
| vnp_PayDate       | Yes | Numeric      | 14      | 20150924080900      ||
| vnp_TransactionNo | Yes | Alpha        | 3, 255  | 20160802055902      | mã giao dịch ghi nhận tại hệ thống vnpay |
| vnp_SecureHash    | Yes | Alphanumeric | 32, 256 | 2a4f22...           | checksum. Creating this depends on merchant configs and api version. SHA256 and MD5 |

difference between TxnRef and TransactionNo? Seems like TxnRef is supposed to be unique on the merchant side, and TransactionNo is unique on vnpay's side. So I can save this down and allow the merchant managers to look up what's being transacted. Nah it's pretty stupid overall, cause I apparently have to still pass over the TransactionNo when querying. So may be TransactionNo is the final, official unique identifier to all parties, and TxnRef to have an additional check against that, and is valid in the period of a day only.

## Merchant querying

| Parameter | Required | Format | Min, Max | Example | Description |
| - | - | - | - | - | - |
| vnp_Version       | Yes | Alphanumeric | 1, 8    | 1                   | Current is 2.0.0 |
| vnp_Command       | Yes | Alpha        | 1, 16   | querydr             | "querydr" |
| vnp_TmnCode       | Yes | Alphanumeric | 8       | VNPAY001            | merchant website on vnpay network |
| vnp_TxnRef        | Yes | Alphanumeric | 1, 100  | VNPAY123            | uuid, to differentiate between orders |
| vnp_OrderInfo     | Yes | Alphanumeric | 1, 255  | Nap 100K ..         | some description, vietnamese, no accented characters |
| vnp_TransactionNo | Yes | Alpha        | 3, 255  | 20160802055902      | mã giao dịch ghi nhận tại hệ thống vnpay |
| vnp_TransDate     | Yes | Numeric      | 14      | 20150924080900      | thời gian ghi nhận giao dịch |
| vnp_CreateDate    | Yes | Numeric      | 14      | 20150924080900      ||
| vnp_IpAddr        | Yes | Alphanumeric | 7, 45   | 123.123.123.123     ||
| vnp_SecureHash    | Yes | Alphanumeric | 32, 256 | 2a4f22...           | checksum. Creating this depends on merchant configs and api version. SHA256 and MD5 |

## Vnpay response

| Parameter | Required | Format | Min, Max | Example | Description |
| - | - | - | - | - | - |
| vnp_TmnCode           | Yes | Alphanumeric | 8       | VNPAY001            | merchant website on vnpay network |
| vnp_TxnRef            | Yes | Alphanumeric | 1, 100  | VNPAY123            | uuid, to differentiate between orders |
| vnp_Amount            | Yes | Numeric      | 1, 12   | 100000              | amount, 100x the vnd amount, so example is 10k VND |
| vnp_OrderInfo         | Yes | Alphanumeric | 1, 255  | Nap 100K ..         | some description, vietnamese, no accented characters |
| vnp_ResponseCode      | Yes | Numeric      | 2       | 00                  | 00 for success for every api |
| vnp_Message           | Yes | Alphanumeric | 10, 255 | Query Success       ||
| vnp_BankCode          | No  | Alpha        | 3, 20   | VIETCOMBANK         | mã ngân hàng phát hành thẻ (client?) |
| vnp_PayDate           | Yes | Numeric      | 14      | 20150924080900      ||
| vnp_TransactionNo     | Yes | Alpha        | 3, 255  | 20160802055902      | mã giao dịch ghi nhận tại hệ thống vnpay |
| vnp_TransactionType   | Yes | Numeric      | 2       | 02                  | 01: processed, 02: full refund, 03: partial refund |
| vnp_TransactionStatus | Yes | Numeric      | 2       | 00                  | transaction status at vnpay. More in 2.5.6.2 |
| vnp_SecureHash        | Yes | Alphanumeric | 32, 256 | 2a4f22...           | checksum. Creating this depends on merchant configs and api version. SHA256 and MD5 |

also expect to have a hash secret given in the merchant's admin page

pretty much how it looks like:
$query .= urlencode($key)
$vnp_Url .= "?" . $query;
$vnpSecureHash = md5($hashSecret . $hashData);
$vnp_Url .= "vnp_SecureHashType=MD5&vnp_SecureHash=" . $vnpSecureHash;

https://merchant.vnpay.vn/
https://vnpayment.vnpay.vn/
http://sandbox.vnpayment.vn/apis/
http://sandbox.vnpayment.vn/devreg/
