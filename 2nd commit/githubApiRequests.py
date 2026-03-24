import requests
import json
import sys


def getUserRepos(username):
    url = f"https://api.github.com/users/{username}/repos"
    response = requests.get(url)

    if response.status_code == 200:
        repos = response.json()
        print(f"\n{username} kullanıcısının {len(repos)} reposu bulundu")

        for i, repo in enumerate(repos):
            print(f"{i+1}. {repo['name']}")

        secim = int(input("\nDetaylı Analiz için repo numarası seçin: "))
        secilenRepo = repos[secim-1]

        stats = {
            "name" : secilenRepo.get("name"),
            "stars" : secilenRepo.get("stargazers_count"),
            "forks" : secilenRepo.get("forks_count"),
            "open_issues" : secilenRepo.get("open_issues_count"),
            "size" : secilenRepo.get("size"),
            "language" : secilenRepo.get("language")

        }

        return stats
    else:
        print("Kullanıcı Bulunamadı")
        return None

if len(sys.argv) > 1:
        user = sys.argv[1]
else:
    user = input("\nAnaliz edilecek profilin adını giriniz: ")

data = getUserRepos(user)

if data:
    with open("repo.data.json","w") as f:
        json.dump(data,f,indent = 4)
        print(f"\nSeçilen repo {data['name']} C++ için hazırlandı.")



