```bash
# mount google-drive, (comment out after first run)
from google.colab import drive
drive.mount('/content/drive')
import os
os.chdir('/content/drive/My Drive')
!pwd
```