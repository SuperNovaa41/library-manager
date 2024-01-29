<script lang="ts" context="module">
  export interface BookEntry {
    id: number;
    isbn: string;
    title: string;
    authors: string;
    imageurl: string;
    publication_year: number;
    page_length: number;
  }
</script>

<script lang="ts">
  export let entry: BookEntry;
</script>

<div class="container">
  <div class="cover" />
  <div class="content" />
</div>

<style>
  .container {
    display: flex;
    flex-direction: column;

    height: 350px;
    border-radius: 10px;
    padding: 10px;
    background-color: blue;

    & .cover {
      width: 100%;
      height: 75%;
      border-radius: 10px;
      background-color: red;
    }

    & .content {
      width: 100%;
      height: 25%;
      margin-top: 10px;
      background-color: magenta;
    }
  }
</style>
