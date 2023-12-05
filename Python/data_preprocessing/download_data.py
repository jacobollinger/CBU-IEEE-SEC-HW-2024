from mega import Mega

def download_data(*mega_links):
    mega = Mega()
    session = mega.login()

    for mega_link in mega_links:
        session.download_url(mega_link)
