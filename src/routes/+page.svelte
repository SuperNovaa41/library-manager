<script lang="ts">
  import Book from "./Book.svelte";
  import type { BookEntry } from "./Book.svelte";

  // TODO: Eventually use the actual API.
  let books: BookEntry[] = JSON.parse(`{
    "books": [
      {
        "id": "1",
        "isbn": "9781338134377",
        "title": "The Silver Eyes (Five Nights At Freddy's #1)",
        "authors": "Scott Cawthon, Kira Breed-Wrisley, Kira Breed-Wrisley, Kira Breed-Wrisley Scott Cawthon, Suzanne Elise Freeman, Kira Breed-Wrisley",
        "imageurl": "https://covers.openlibrary.org/b/id/8075533-L.jpg",
        "publication_year": "2001",
        "progress": "312",
        "page_length": "400"
      },
      {
        "id": "2",
        "isbn": "1338741187",
        "title": "Official Five Nights at Freddy's Coloring Book",
        "authors": "Scott Cawthon",
        "imageurl": "https://covers.openlibrary.org/b/id/12405670-L.jpg",
        "publication_year": "2021",
        "progress": "12",
        "page_length": "96"
      },
      {
        "id": "3",
        "isbn": "9781338792676",
        "title": "Five nights at freddy's",
        "authors": "Scott Cawthon",
        "imageurl": "https://covers.openlibrary.org/b/id/10502812-L.jpg",
        "publication_year": "2018",
        "progress": "0",
        "page_length": "166"
      },
      {
        "id": "4",
        "isbn": "9781338767681",
        "title": "Freddy Files",
        "authors": "Scott Cawthon",
        "imageurl": "https://covers.openlibrary.org/b/id/14432108-L.jpg",
        "publication_year": "2019",
        "progress": "256",
        "page_length": "256"
      },
      {
        "id": "5",
        "isbn": "9781419747496",
        "title": "The Art of The Mitchells vs. The Machines",
        "authors": "Ramin Zahed",
        "imageurl": "https://covers.openlibrary.org/b/id/13771830-L.jpg",
        "publication_year": "2020",
        "progress": "128",
        "page_length": "224"
      }
    ]}`).books;
</script>

<div class="container">
  {#each books as book}
    <Book entry={book} />
  {/each}
</div>

<style>
  .container {
    height: 100%;
    width: 100%;
    display: grid;
    grid-template-columns: repeat(auto-fill, 200px);
    grid-gap: 25px;
    padding: 25px;
  }
</style>
