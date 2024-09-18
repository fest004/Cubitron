import clsx from 'clsx';
import Link from '@docusaurus/Link';
import useDocusaurusContext from '@docusaurus/useDocusaurusContext';
import Layout from '@theme/Layout';
import styles from './index.module.css';

// Background image
import bgImage from "@site/static/img/render.png";

export default function Home(): JSX.Element {
  const {siteConfig} = useDocusaurusContext();

  return (
    <Layout>
      <main className={styles.main}>
        <div className={styles.background}></div>
        <div className={styles.content}>
          <div className={styles.buttons}>
            <Link
              className="button button--secondary button--lg"
              to="/docs/intro"
            >
              Read ⟶
            </Link>
          </div>
        </div>
      </main>
    </Layout>
  );
}
